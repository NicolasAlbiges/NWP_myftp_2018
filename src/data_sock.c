/*
** EPITECH PROJECT, 2019
** ptr_fct.c
** File description:
** myftp
*/

#include "main.h"

void neutralize_data_sock(client_t *client)
{
    client->fd_port = -1;
    client->fd_port_client = -1;
}

void kill_data_sock(client_t *client, fd_set *active_fd_set)
{
    if (client->fd_port != -1 && client->fd_port_client != -1) {
        if (client->fd_port != -2) {
            FD_CLR(client->fd_port, active_fd_set);
            close(client->fd_port);
        }
        close(client->fd_port_client);
    }
    neutralize_data_sock(client);
}

int is_fd_data_sock(int fd, client_t *client)
{
    while (client != NULL) {
        if (fd == client->fd_port) {
            return (0);
        }
        client = client->next;
    }
    return (-1);
}

int generate_port(int fd, client_t *client)
{
    int port = 1034;

    client->data_sock_addr.sin_port = htons(port);
    client->data_sock_addr.sin_addr.s_addr = INADDR_ANY;
    client->data_sock_addr.sin_family = AF_INET;
    while (bind(fd, (struct sockaddr *)&client->data_sock_addr,
sizeof(struct sockaddr_in)) == -1) {
        if (errno == EADDRINUSE) {
            port = rand() % 40000 + 1024;
            client->data_sock_addr.sin_port = htons(port);
            client->port = htons(port);
        } else
            return (-1);
    }
    return (port);
}

int data_socket(server_t* server, client_t *client)
{
    int opt = 1;

    client->fd_port = socket(AF_INET, SOCK_STREAM, 0);
    if (client->fd_port == -1) {
        fprintf(stderr, "Error opening socket.\n");
        return (84);
    }
    if ((client->data_port = generate_port(client->fd_port, client)) == -1)
        return (84);
    setsockopt(client->fd_port, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    &opt, sizeof(opt));
    if (listen(client->fd_port, 1) < 0) {
        fprintf(stderr, "Listen faild.\n");
        return (84);
    }
    FD_SET(client->fd_port, &server->active_fd_set);
    return (0);
}