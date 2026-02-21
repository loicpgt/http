/*
 * [2026-02-20] File created by loicpgt
 *
 *  Comments:
 */

#define IS_SOCKET_REUSABLE 1

#include "socket.h"
#include "kernel.h"

#include <stdlib.h>
#include <netinet/in.h>

typedef struct network_socket {
    int socket_fd;
    struct sockaddr_in address;
    socklen_t address_len;
} network_socket_t;

network_socket_t* create_network_socket(int port) {
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