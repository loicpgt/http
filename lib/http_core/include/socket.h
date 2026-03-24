/*
 * [2026-02-20] File created by loicpgt
 *
 *  Comments:
 */

#ifndef HTTP_SOCKET_H
#define HTTP_SOCKET_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct network_socket network_socket_t;
typedef struct network_message network_message_t;
typedef struct network_message_queue network_message_queue_t;

/**
 * @brief Creates a new network socket for the running process to use
 * @param port The port for the socket
 * @return The created network socket struct
 */
network_socket_t* bind_network_socket(int port);
void close_network_socket(network_socket_t* socket);

/**
 * Starts a listening thread and fills the message queue as connections are registered
 * @param socket The socket to use
 * @param queue The message to queue to send the messages to
 */
void listen_on_network_socket(network_socket_t* socket, network_message_queue_t* queue);

/**
 *
 */
network_message_queue_t* init_message_queue(size_t queue_size);
void clear_message_queue(network_message_queue_t* queue);

/**
 *
 * @param queue
 * @return
 */
network_message_t* get_next_message(const network_message_queue_t* queue);

/**
 *
 * @param message
 * @param content
 */
void respond_to(network_message_t* message, const char* content);

#ifdef __cplusplus
    }
#endif

#endif //HTTP_SOCKET_H