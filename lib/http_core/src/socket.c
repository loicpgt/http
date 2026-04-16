/*
 * [2026-02-20] File created by loicpgt
 *
 *  Comments:
 */

#define IS_SOCKET_REUSABLE 1

#include "core/net/socket.h"
#include "core/kernel.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

typedef struct network_socket {
    int socket_fd;
    struct sockaddr_in address;
    socklen_t address_len;
} network_socket_t;

typedef struct network_message {
    int socket_fd;
    uint8_t used;
} network_message_t;

typedef struct network_message_queue {
    size_t size;
    network_message_t* memory_region;
} network_message_queue_t;

network_socket_t* bind_network_socket(int port) {
    const int opt = IS_SOCKET_REUSABLE;
    network_socket_t *network_socket = malloc(sizeof(network_socket_t));

    network_socket->socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (network_socket->socket_fd < 0) {
        PANIC("INTERNAL_ERROR", "Failed to create socket.");
    }

    if (setsockopt(network_socket->socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        PANIC("INTERNAL_ERROR", "Failed to set reusable socket.");
    }

    network_socket->address.sin_family = AF_INET;
    network_socket->address.sin_addr.s_addr = htonl(INADDR_ANY);
    network_socket->address.sin_port = htons(port);
    network_socket->address_len = sizeof(network_socket->address);

    if (bind(network_socket->socket_fd, (struct sockaddr *) &network_socket->address, sizeof(network_socket->address)) < 0) {
        PANIC("INTERNAL_ERROR", "Failed to bind socket.");
    }

    return network_socket;
}

void close_network_socket(network_socket_t *socket) {
    close(socket->socket_fd);
    socket->socket_fd = 0;
    free(socket);
}

void listen_on_network_socket(network_socket_t *socket, network_message_queue_t *queue) {
    if (listen(socket->socket_fd, queue->size) < 0) {
        PANIC("INTERNAL_ERROR", "Failed to listen on socket.");
    }

    int tmp_socket;
    if ((tmp_socket = accept(socket->socket_fd, (struct sockaddr*)&socket->address, &socket->address_len)) < 0) {
        PANIC("INTERNAL_ERROR", "Failed to accept connection from socket.");
    }

    LOG_INFO("Accepted connection...");
    network_message_t* msg = NULL;
    for (int i = 0; i < queue->size; i++) {
        msg = &queue->memory_region[i * sizeof(network_message_t)];
        if (msg->used == 0 || msg->socket_fd == 0) {
            LOG_TRACE("New connection assigned to msg if %d", i);
            break;
        }
    }

    if (msg == NULL) {
        PANIC("INTERNAL_ERROR", "No available message in the queue.");
    }

    msg->socket_fd = tmp_socket;
}

network_message_queue_t* init_message_queue(const size_t queue_size) {
    network_message_queue_t *queue = malloc(sizeof(network_message_queue_t));
    queue->size = queue_size;

    queue->memory_region = calloc(queue_size, sizeof(network_message_t));
    if (queue->memory_region == NULL) {
        PANIC("INTERNAL_ERROR", "Failed to allocate memory for queue.");
    }

    network_message_t *msg = NULL;
    for (int i = 0; i < queue_size; i++) {
        msg = &queue->memory_region[i * sizeof(network_message_t)];
        msg->used = 0;
        msg->socket_fd = 0;
    }

    return queue;
}

void clear_message_queue(network_message_queue_t *queue) {
    free(queue->memory_region);
    free(queue);
}

network_message_t * get_next_message(const network_message_queue_t *queue) {
    for (int i = 0; i < queue->size; i++) {
        network_message_t* msg = &queue->memory_region[i * sizeof(network_message_t)];
        if (msg->used) {
            continue;
        }

        msg->used = 1;
        return msg;
    }

    return NULL;
}

void respond_to(network_message_t *message, const char* content) {
    if (message->socket_fd < 0) {
        PANIC("INTERNAL_ERROR", "Cannot send message to an empty socket.");
    }

    if (send(message->socket_fd, content, strlen(content), 0) < -1) {
        PANIC("INTERNAL_ERROR", "Failed to send message to an empty socket.");
    }

    close(message->socket_fd);
    message->used = 0;
    message->socket_fd = 0;
}

char* get_msg_content(const network_message_t *msg) {
    char* content = malloc(sizeof(char) * 1024);
    if (!content) return NULL;

    memset(content, 0, 1024);

    const ssize_t bytes_read = read(msg->socket_fd, content, 1023);

    if (bytes_read < 0) {
        free(content);
        return NULL;
    }

    content[bytes_read] = '\0';

    return content;
}
