/*
 * [2026-02-20] File created by loicpgt
 *
 *  Comments:
 */

#ifndef HTTP_SOCKET_H
#define HTTP_SOCKET_H

typedef struct network_socket network_socket_t;

/**
 * @brief Creates a new network socket for the running process to use
 * @param port The port for the socket
 * @return The created network socket struct
 */
network_socket_t* create_network_socket(int port);

#endif //HTTP_SOCKET_H