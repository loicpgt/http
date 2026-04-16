#include "core/http.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/kernel.h"

struct header_map_entry {
    const char key[128];
    const char* value[256];
};

struct header_map {
    size_t capacity;
    size_t length;
    struct header_map_entry* memory_region;
};

typedef struct http_request {
    char protocol[15];
    char path[256];
    char origin[15];
    char* headers;
    char* body;
} http_request_t;

typedef struct http_response {

} http_response_t;

typedef struct http_context {
    http_request_t request;
    http_response_t response;
} http_context_t;

void header_map_clear(struct header_map* map) {
    map->capacity = 0;
    map->length = 0;
    free(map->memory_region);
    map->memory_region = NULL;
}

void header_map_resize(struct header_map* map, size_t capacity) {
    if (map->memory_region != NULL) {
        header_map_clear(map);
    }

    map->capacity = capacity;
    map->memory_region = calloc(sizeof(struct header_map), map->capacity);
    if (map->memory_region == NULL) {
        PANIC("Failed to resize map");
    }

    map->length = 0;
}

void header_map_extend(struct header_map* map, size_t capacity) {
    map->capacity += capacity;
    map->memory_region = realloc(map, sizeof(struct header_map) * map->capacity);

    if (map->memory_region == NULL) {
        PANIC("Failed to extend map");
    }
}

int header_map_emplace(struct header_map* map, const char* key, const char* value, size_t idx) {
    if (idx > map->capacity - 1) {
        LOG_ERROR("Index out of bound");
        return -1;
    }

    if (map->length >= map->capacity) {
        header_map_extend(map, 2);
    }



    return 0;
}

size_t header_map_size(const struct header_map* map) {
    return map->length;
}

int header_map_push(struct header_map* map, const char* key, const char* value) {
    if (map->length == map->capacity) {
        header_map_extend(map, map->capacity / 2);
    }


}

void decompose_http_request(http_request_t* request, const network_message_t* msg) {
    char* content = get_msg_content(msg);
    const size_t content_len = strlen(content);

    // Protocol
    for (int i = 0; i < content_len; i++) {
        if (content[i] == '\n') {

        }
    }

    free(content);
}

http_context_t* init_context(const network_message_t *msg) {
    http_context_t* context = (http_context_t*)malloc(sizeof(http_context_t));
    decompose_http_request(&context->request, msg);
    return context;
}
