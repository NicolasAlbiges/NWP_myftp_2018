/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

char *download_file(FILE *filedes)
{
    char *msg = "";
    char *buffer = NULL;

    if (filedes == NULL) {
        fprintf(stderr, "Wrong gestion of memory. \n");
        exit(84);
    }
    while ((buffer = my_getline_file(filedes)) != NULL) {
        msg = my_strcat(msg, buffer);
    }
    return (msg);
}

int write_file(char *path, char *file, char *msg)
{
    int fd = 0;

    if (path[strlen(path) - 1] != '/')
        path = my_strcat(path, "/");
    file = my_strcat(path, file);
    if (access(file, F_OK) != -1)
        fd = open(file, O_WRONLY | O_APPEND | O_TRUNC);
    else
        fd = open(file, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        return (84);
    }
    write(fd, msg, strlen(msg));
    return (0);
}

int storage(char *path, client_t *client, UNUSED server_t* server)
{
    char *msg = NULL;
    int status = 0;

    write(client->fd, RETR, strlen(RETR));
    if ((status = fork()) == -1)
        return (84);
    if (status == 0) {
        msg = download_file(fdopen(client->fd_port_client, "r"));
        if (write_file(client->path, path, msg) == 84) {
            write(client->fd, ERR431, strlen(ERR431));
            kill_data_sock(client, &server->active_fd_set);
            exit(84);
        }
        write(client->fd, END_DATA, strlen(END_DATA));
        exit(0);
    }
    kill_data_sock(client, &server->active_fd_set);
    return (0);
}

int stor(char **arr, client_t *client, server_t* server)
{
    if (client->status == -1) {
        write(client->fd, ERR530, strlen(ERR530));
        return (84);
    }
    if (client->fd_port_client == -1) {
        write(client->fd, ERR425, strlen(ERR425));
        return (84);
    }
    if (arr[1] != NULL) {
        return (storage(my_strcat(client->path, arr[1]), client, server));
    }
    write(client->fd, ERR501, strlen(ERR501));
    kill_data_sock(client, &server->active_fd_set);
    return (0);
}