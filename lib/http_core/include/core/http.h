#ifndef HTTP_HTTP_H
#define HTTP_HTTP_H
#include <sys/types.h>

#include "net/socket.h"

#ifdef __cplusplus
extern "C" {
#endif
    enum HTTP_STATUS_CODE {
        OK = 200,
        CREATED = 201,
        NO_CONTENT = 204,
        BAD_REQUEST = 400,
        UNAUTHORIZED = 401,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        INTERNAL_SERVER = 501,
    };

    struct header_map_entry {
        const char key[128];
        const char value[256];
    };

    struct header_map {
        size_t capacity;
        size_t length;
        struct header_map_entry* memory_region;
    };

    typedef struct http_request {
        char protocol[5];
        char path[256];
        char* body;
        struct header_map headers;
    } http_request_t;

    typedef struct http_response {
        u_int16_t status;
        struct header_map headers;
        char message[4096];
    } http_response_t;

    typedef struct http_context {
        http_request_t request;
        http_response_t response;
    } http_context_t;

    void header_map_clear(struct header_map* map);
    void header_map_resize(struct header_map* map, const size_t capacity);
    int header_map_extend(struct header_map* map, const size_t capacity);
    int header_map_emplace(struct header_map* map, const char* key, const char* value, const size_t idx);
    size_t header_map_size(const struct header_map* map);
    int header_map_push(struct header_map* map, const char* key, const char* value);

    http_context_t* init_context(const network_message_t* msg);
    void http_request_to_string(char* out, const struct http_response* response);
#ifdef __cplusplus
}
#endif

#endif //HTTP_HTTP_H