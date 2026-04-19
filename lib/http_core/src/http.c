#include "core/http.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/kernel.h"

void header_map_clear(struct header_map* map) {
    map->capacity = 0;
    map->length = 0;
    free(map->memory_region);
    map->memory_region = NULL;
}

void header_map_resize(struct header_map* map, const size_t capacity) {
    if (map->memory_region != NULL) {
        header_map_clear(map);
    }

    map->capacity = capacity;
    map->memory_region = calloc(capacity, sizeof(struct header_map));
    if (map->memory_region == NULL) {
        PANIC("Failed to resize map");
    }

    map->length = 0;
}

int header_map_extend(struct header_map* map, const size_t capacity) {
    map->capacity += capacity;
    struct header_map_entry *tmp= realloc(map->memory_region,
                                 sizeof(struct header_map_entry) * map->capacity);

    if (tmp == NULL) {
        LOG_WARN("Failed to extend map");
        return -1;
    }

    map->memory_region = tmp;

    return 1;
}

int header_map_emplace(struct header_map* map, const char* key, const char* value, const size_t idx) {
    if (idx > map->capacity - 1) {
        LOG_ERROR("Index out of bound");
        return -1;
    }

    if (map->length >= map->capacity
            && header_map_extend(map, 2) < 1) {
        LOG_INFO("Emplace aborted");
        return -1;
    }

    struct header_map_entry* entry = &map->memory_region[idx];
    strcpy((char*)&entry->key, key);
    strcpy((char*)&entry->value, value);
    map->length++;

    return 1;
}

size_t header_map_size(const struct header_map* map) {
    return map->length;
}

int header_map_push(struct header_map* map, const char* key, const char* value) {
    if (map->length == map->capacity) {
        header_map_extend(map, map->capacity / 2 + 1);
    }

    return header_map_emplace(map, key, value, map->length);
}

void decompose_http_request(http_request_t* request, const network_message_t* msg) {
    char *content = get_msg_content(msg);
    char* buffer = malloc(sizeof(char) * 1024);
    strcpy(buffer, content);

    // Protocol
    char* token = strtok(buffer, " ");
    if (strcpy(request->protocol, token) <= 0) {
        PANIC("Failed to get protocol string");
    }

    // Path
    token = strtok(NULL, " ");
    if (strcpy(request->path, token) <= 0) {
        PANIC("Failed to get path string");
    }

    // Resets the damaged line from the strtok operation
    strcpy(buffer, content);
    strtok(buffer, "\n"); // Skips the first line
    token = NULL;

    if (header_map_size(&request->headers) == 0) {
        header_map_resize(&request->headers, 5);
    }

    while (1) {
        // Gets the next line
        token = strtok(NULL, "\n");
        if (token == NULL || token[0] == '\r') {
            break;
        }

        char key[128], value[128];
        u_int8_t flag = 0;
        u_int8_t offset = 0;
        const size_t len = strlen(token);

        for (size_t i = 0; i < len; i++) {
            if (token[i] == ':' && token[i + 1] == ' ') {
                i++;
                flag = 1;
                offset = 0;
                continue;
            }

            if (flag) {
                value[offset] = token[i];
                value[offset + 1] = '\0';
            }
            else {
                key[offset] = token[i];
                key[offset + 1] = '\0';
            }
            offset++;
        }

        header_map_push(&request->headers, key, value);
    }

    free(buffer);
    free(content);
}

http_context_t* init_context(const network_message_t *msg) {
    http_context_t* context = (http_context_t*)malloc(sizeof(http_context_t));
    decompose_http_request(&context->request, msg);

    return context;
}

#define STATUS_CODE_TRANSLATOR(code, text) (status_code == code) { strcat(out, text); return;}
void status_code_str(char* out, const u_int16_t status_code) {
    if STATUS_CODE_TRANSLATOR(201, "201 Accepted")
    if STATUS_CODE_TRANSLATOR(204, "204 No Content")
    if STATUS_CODE_TRANSLATOR(404, "404 Not Found")
    strcat(out, "200 OK");
}

void http_request_to_string(char *out, const struct http_response *response) {
    strcpy(out, "HTTP/1.1 ");
    status_code_str(out, response->status);

    const size_t header_len = header_map_size(&response->headers);
    for (size_t i = 0; i < header_len; i++) {
        strcat(out, "\n");
        strcat(out, response->headers.memory_region[i].key);
        strcat(out, ": ");
        strcat(out, response->headers.memory_region[i].value);
    }

    strcat(out, "\n\n");
    strcat(out, response->message);
    strcat(out, "\n\0");
}
