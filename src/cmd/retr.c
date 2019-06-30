/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

char *upload_file(FILE *filedes)
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

int retrieve(char *path, client_t *client, server_t* server)
{
    char *msg = NULL;
    int status = 0;

    if (access(path, F_OK) == -1) {
        write(client->fd, ERR550, strlen(ERR550));
        kill_data_sock(client, &server->active_fd_set);
        return (84);
    }
    write(client->fd, RETR, strlen(RETR));
    if ((status = fork()) == -1)
        return (84);
    if (status == 0) {
        msg = upload_file(fopen(path, "r"));
        write(client->fd_port_client, msg, strlen(msg));
        write(client->fd, END_DATA, strlen(END_DATA));
        exit(0);
    }
    kill_data_sock(client, &server->active_fd_set);
    return (0);
}

int retr(char **arr, client_t *client, server_t* server)
{
    if (client->status == -1) {
        write(client->fd, ERR530, strlen(ERR530));
        return (84);
    }
    if (client->fd_port_client == -1) {
        write(client->fd, ERR425, strlen(ERR425));
        return (84);
    }
    if (arr[1] != NULL)
        return (retrieve(my_strcat(client->path, arr[1]), client, server));
    write(client->fd, ERR501, strlen(ERR501));
    kill_data_sock(client, &server->active_fd_set);
    return (0);
}