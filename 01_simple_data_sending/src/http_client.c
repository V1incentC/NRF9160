// http_client.c
#include "http_client.h"
#include "api_response_parser.h"
#include "app_config.h"
#include "shared_data.h"
#include <zephyr/net/socket.h>
#include <zephyr/net/tls_credentials.h>
#include <zephyr/net/http/client.h>
#include <modem/nrf_modem_lib.h>
#include <modem/modem_key_mgmt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define TLS_SEC_TAG 42
#define PDN_IPV6_WAIT_MS 1000

/* Certificate for `api.beescales.com` */
static const char cert[] = {
#include "../cert/lets-encrypt-r3"
};
/* Setup TLS options on a given socket */
static int tls_setup(int fd)
{
	int err;
	int verify;

	/* Security tag that we have provisioned the certificate with */
	const sec_tag_t tls_sec_tag[] = {
		TLS_SEC_TAG,
	};

#if defined(CONFIG_SAMPLE_TFM_MBEDTLS)
	err = tls_credential_add(tls_sec_tag[0], TLS_CREDENTIAL_CA_CERTIFICATE, cert, sizeof(cert));
	if (err)
	{
		return err;
	}
#endif

	/* Set up TLS peer verification */
	enum
	{
		NONE = 0,
		OPTIONAL = 1,
		REQUIRED = 2,
	};

	verify = REQUIRED;

	err = setsockopt(fd, SOL_TLS, TLS_PEER_VERIFY, &verify, sizeof(verify));
	if (err)
	{
		printk("Failed to setup peer verification, err %d\n", errno);
		return err;
	}

	/* Associate the socket with the security tag
	 * we have provisioned the certificate with.
	 */
	err = setsockopt(fd, SOL_TLS, TLS_SEC_TAG_LIST, tls_sec_tag, sizeof(tls_sec_tag));
	if (err)
	{
		printk("Failed to setup TLS sec tag, err %d\n", errno);
		return err;
	}

	err = setsockopt(fd, SOL_TLS, TLS_HOSTNAME, HTTPS_HOSTNAME, sizeof(HTTPS_HOSTNAME) - 1);
	if (err)
	{
		printk("Failed to setup TLS hostname, err %d\n", errno);
		return err;
	}
	return 0;
}
static void http_response_cb(struct http_response *rsp, enum http_final_call final_data, void *user_data) {
	
	struct shared_data *sd = shared_data_get();
    /* Handle the response data here */
	/* Print the response data */
    //printk("Received data:\n%.*s\n", rsp->data_len, rsp->body_frag_start);
	/* Copy the response data */
	k_mutex_lock(&sd->url_mutex, K_FOREVER);
	memcpy(sd->response_buf, rsp->body_frag_start, rsp->body_frag_len);
	sd->response_len = rsp->body_frag_len;
	k_mutex_unlock(&sd->url_mutex);
	/* Signal the semaphore */
	k_sem_give(&sd->http_response_sem);
}

int http_client_send_get_request(const char *url) {
    int err;
    int fd;
    struct addrinfo *res;
    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct http_request req = {0};
    static uint8_t recv_buf[HTTP_RESPONSE_BUF_SIZE];
	struct shared_data *sd = shared_data_get();

	k_mutex_lock(&sd->url_mutex, K_FOREVER);
    /* Format HTTP request */
    req.method = HTTP_GET;
    req.url = url;
    req.host = HTTPS_HOSTNAME;
    req.protocol = "HTTP/1.1";
    req.response = http_response_cb;
    req.recv_buf = recv_buf;
    req.recv_buf_len = sizeof(recv_buf);
	k_mutex_unlock(&sd->url_mutex);

    /* Resolve hostname */
    err = getaddrinfo(HTTPS_HOSTNAME, HTTPS_PORT, &hints, &res);
    if (err) {
        printk("Failed to resolve hostname %s, error: %d\n", HTTPS_HOSTNAME, err);
        return err;
    }

    /* Create socket */
    fd = socket(res->ai_family, SOCK_STREAM, IPPROTO_TLS_1_2);
    if (fd < 0) {
        printk("Failed to create socket, error: %d\n", errno);
        err = -errno;
        goto clean_up;
    }

	/* Setup TLS socket options */
	err = tls_setup(fd);
	if (err) {
		goto clean_up;
	}

	/* Connect to server */
	((struct sockaddr_in *)res->ai_addr)->sin_port = htons(HTTP_PORT);
	err = connect(fd, res->ai_addr, res->ai_addrlen);
	if (err < 0) {
		printk("Failed to connect to server, error: %d\n", errno);
		err = -errno;
		goto clean_up;
	}

	/* Send HTTP request */
	err = http_client_req(fd, &req, 5000, NULL);
	if (err < 0) {
		printk("Failed to send HTTP request, error: %d\n", errno);
		err = -errno;
		goto clean_up;
	}

clean_up:
	freeaddrinfo(res);
	close(fd);

	return err;
}

void fetch_and_parse_json_response(const char *imei) {

    struct shared_data *sd = shared_data_get(); // Get shared data instance

    char url[HTTP_URL_BUF_SIZE];
    snprintf(url, sizeof(url), "/v3.0/config?id=%s", imei);

    int err = http_client_send_get_request(url); // Use shared data instance
    if (err < 0) {
        printk("Failed to get JSON response from server, error: %d\n", err);
        return;
    }

    k_sem_take(&sd->http_response_sem, K_FOREVER);
	k_mutex_lock(&sd->url_mutex, K_FOREVER);
    printk("Received JSON response (%d bytes):\n%s\n", sd->response_len, sd->response_buf);

    // Parse JSON response
    api_response_parser_json(sd->response_buf, &sd->json_response);
	k_mutex_unlock(&sd->url_mutex);
    memcpy(sd->api_key, sd->json_response.settings[0].c1, sizeof(sd->api_key));
    printk("Extracted c1 key: %s\n", sd->api_key);
    k_sem_give(&sd->api_key_sem);
}