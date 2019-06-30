/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

void read_from_client(FILE *filedes, client_t *client, server_t* server)
{
    char *buffer;
    char **arr;
    char *operator[] = {" ", "\t", "\r", "\n", NULL};

    while ((buffer = my_getline(filedes)) != NULL) {
        client->cmd = strdup(buffer);
        arr = word_array(buffer, operator);
        pointer_fct(arr, client, server);
        free(buffer);
        return;
    }
}

int accept_client(int fd_sock, server_t* server, client_t *client, int mode)
{
    int fd_new = 0;
    size_t size = 0;

    if (mode == 0) {
        size = sizeof(server->addr);
        fd_new = accept(fd_sock, (struct sockaddr *)&server->addr,
        (socklen_t *restrict)&size);
    } else {
        size = sizeof(client->data_sock_addr);
        fd_new = accept(fd_sock, (struct sockaddr *)&client->data_sock_addr,
        (socklen_t *restrict)&size);
    }
    if (fd_new < 0) {
        fprintf(stderr, "Accept failed.\n");
        return (-1);
    }
    return (fd_new);
}

int create_client_read(int sock, server_t* server, int fd)
{
    int new;
    client_t *client = server->head;

    if (fd == sock) {
        if ((new = accept_client(sock, server, client, 0)) == -1)
            return (84);
        FD_SET(new, &server->active_fd_set);
        write(new, LOG, strlen(LOG));
        server->head = fill_client(server->head, server->path, new);
    } else if (is_fd_data_sock(fd, server->head) == 0) {
        client = which_client(fd, server->head, 1);
        client->fd_port_client = accept_client(fd, server, client, 1);
        if (client->fd_port_client == -1)
            return (84);
    } else {
        read_from_client(fdopen(fd, "r"),
        which_client(fd, server->head, 0), server);
        server->head = free_client_quit(server->head, &server->active_fd_set);
    }
    return (0);
}

int client_side_isset(int sock, server_t* server, int fd)
{
    if (FD_ISSET(fd, &server->read_fd_set))
        return (create_client_read(sock, server, fd));
    return (0);
}

int client_side(int sock, server_t* server)
{
    int fd = 0;

    for (fd = FD_SETSIZE; fd > 0; -- fd)
        if (client_side_isset(sock, server, fd) == 84)
            return (84);
    return (0);
}
