// api_response_parser.c
#include "api_response_parser.h"

int api_response_parser_json(const char *response, struct api_response *resp) {

	int err;

	/* Find the start of the JSON body */
	char *json_start = strstr(response, "{");
	if (json_start == NULL) {
		return -1;
	}

	/* Find the end of the JSON body */
	char *json_end = strrchr(json_start, '}');
	if (json_end == NULL) {
		return -1;
	}
	json_end++; // Include the closing brace

	/* Parse JSON response */
	err = json_obj_parse(json_start, json_end - json_start, response_descr,
						 ARRAY_SIZE(response_descr), resp);
	if (err < 0) {
		return err;
	}

	return 0;
}
