// api_response_parser.h
#ifndef API_RESPONSE_PARSER_H
#define API_RESPONSE_PARSER_H

#include <zephyr/data/json.h>


struct api_settings {
    const char* ci;
    const char* c1;
    struct json_obj_token o1;
    struct json_obj_token o2;
    struct json_obj_token f1;
    struct json_obj_token f2;
    const char* gp;
    const char* ac;
    int at;
    const char* we;
    int wa;
    int al;
    int ui;
    const char* ah;
    const char* df;
    const char* te;
    const char* ap;
    const char* hs;
    bool go;
    int tz;
    const char* ps;
    const char* us;
    int zs;
    int ks;
    const char* ln;
};

struct api_response {
    struct api_settings settings[1];
    size_t settings_len;
};

static const struct json_obj_descr api_settings_descr[] = {
    JSON_OBJ_DESCR_PRIM(struct api_settings, ci, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct api_settings, c1, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct api_settings, o1, JSON_TOK_FLOAT ),
    JSON_OBJ_DESCR_PRIM(struct api_settings, o2, JSON_TOK_FLOAT ),
    JSON_OBJ_DESCR_PRIM(struct api_settings, f1, JSON_TOK_FLOAT ),
    JSON_OBJ_DESCR_PRIM(struct api_settings, f2, JSON_TOK_FLOAT ),
    JSON_OBJ_DESCR_PRIM(struct api_settings, gp, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct api_settings, ac, JSON_TOK_STRING),
	JSON_OBJ_DESCR_PRIM(struct api_settings, at, JSON_TOK_NUMBER),
	JSON_OBJ_DESCR_PRIM(struct api_settings, we, JSON_TOK_STRING),
	JSON_OBJ_DESCR_PRIM(struct api_settings, wa, JSON_TOK_NUMBER),
	JSON_OBJ_DESCR_PRIM(struct api_settings, al, JSON_TOK_NUMBER),
	JSON_OBJ_DESCR_PRIM(struct api_settings, ui, JSON_TOK_NUMBER),
	JSON_OBJ_DESCR_PRIM(struct api_settings, ah, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct api_settings, df, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct api_settings, te, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct api_settings, ap, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct api_settings, hs, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct api_settings, go, JSON_TOK_TRUE),
    JSON_OBJ_DESCR_PRIM(struct api_settings, tz, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct api_settings, ps, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct api_settings, us, JSON_TOK_STRING),
    JSON_OBJ_DESCR_PRIM(struct api_settings, zs, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct api_settings, ks, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(struct api_settings, ln, JSON_TOK_STRING)
};

static const struct json_obj_descr response_descr[] = {
    JSON_OBJ_DESCR_OBJ_ARRAY(struct api_response, settings, 1,
                             settings_len, api_settings_descr,
                             ARRAY_SIZE(api_settings_descr)),
};

int api_response_parser_json(const char *response, struct api_response *resp);

#endif // API_RESPONSE_PARSER_H
