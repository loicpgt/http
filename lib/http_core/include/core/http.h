#ifndef HTTP_HTTP_H
#define HTTP_HTTP_H
#include "net/socket.h"

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct http_context http_context_t;
    typedef struct http_request http_request_t;
    typedef struct http_response http_response_t;

    http_context_t* init_context(const network_message_t* msg);
#ifdef __cplusplus
}
#endif

#endif //HTTP_HTTP_H