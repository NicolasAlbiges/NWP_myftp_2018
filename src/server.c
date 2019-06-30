/*
** EPITECH PROJECT, 2019
** ptr_fct.c
** File description:
** myftp
*/

#include "main.h"

void free_server(server_t* server)
{
    while (server->head != NULL) {
        server->head->status = 1;
        server->head = free_client_quit(server->head, &server->active_fd_set);
    }
    free(server);
}

int run(int sock, server_t* server)
{
    while (1) {
        server->read_fd_set = server->active_fd_set;
        if (select (FD_SETSIZE, &server->read_fd_set, NULL, NULL, NULL) < 0) {
            fprintf(stderr, "Select faild\n");
            return (-1);
        }
        client_side(sock, server);
    }
}

int start_server(server_t* server, int fd)
{
    int opt = 1;

    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (listen(fd, 1) < 0) {
        fprintf(stderr, "Listen faild.\n");
        return (84);
    }
    FD_ZERO(&server->active_fd_set);
    FD_SET(fd, &server->active_fd_set);
    run(fd, server);
    return (0);
}

int server(server_t* server)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1) {
        fprintf(stderr, "Error opening socket.\n");
        free_server(server);
        return (84);
    }
    server->addr.sin_port = htons(server->port);
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->addr.sin_family = AF_INET;
    if (bind(fd, (struct sockaddr *)&server->addr,
    sizeof(struct sockaddr_in)) == -1) {
        fprintf(stderr, "Error binding socket.\n");
        free_server(server);
        return (84);
    }
    if (start_server(server, fd) == 84)
        return (84);
    free_server(server);
    return (0);
}

server_t *init_server(int port, char *path)
{
    server_t* new_node = malloc(sizeof(server_t));

    new_node->port = port;
    new_node->path = realpath(path, NULL);
    new_node->path = my_strcat(new_node->path, "/");
    new_node->status = 0;
    new_node->head = NULL;
    return (new_node);
}