/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int path_name_exist(char **arr)
{
    for (int ct = 0; arr[ct] != NULL; ct ++)
        if (access(arr[1], F_OK) == -1) {
            return (84);
        }
    return (0);
}

char *cmd_path(char *path)
{
    char *msg = "";
    char *buffer = NULL;
    FILE *filedes = popen(my_strcat("ls -la ", path), "r");

    if (filedes == NULL) {
        fprintf(stderr, "Wrong gestion of memory. \n");
        exit(84);
    }
    while ((buffer = my_getline_file(filedes)) != NULL) {
        msg = my_strcat(msg, buffer);
    }
    return (msg);
}

int listage(char **arr, client_t *client, server_t* server)
{
    char *msg = NULL;
    int status = 0;

    if (path_name_exist(arr) == 84) {
        write(client->fd, ERR550, strlen(ERR550));
        kill_data_sock(client, &server->active_fd_set);
        return (84);
    }
    write(client->fd, RETR, strlen(RETR));
    if ((status = fork()) == -1)
        return (84);
    if (status == 0) {
        msg = cmd_path(arr[1]);
        write(client->fd_port_client, msg, strlen(msg));
        write(client->fd, END_DATA, strlen(END_DATA));
        exit(0);
    }
    kill_data_sock(client, &server->active_fd_set);
    return (0);
}

int listage_empty(client_t *client, server_t* server, char *path)
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
        msg = cmd_path(path);
        write(client->fd_port_client, msg, strlen(msg));
        write(client->fd, END_DATA, strlen(END_DATA));
        exit(0);
    }
    kill_data_sock(client, &server->active_fd_set);
    return (0);
}

int list(char **arr, client_t *client, server_t* server)
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
        return (listage(arr, client, server));
    else
        return (listage_empty(client, server, client->path));
    return (0);
}