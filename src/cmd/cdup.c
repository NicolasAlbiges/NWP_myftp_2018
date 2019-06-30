/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int parent_path(char *new_path, client_t *client, server_t* server)
{
    if (strlen(server->path) > strlen(new_path)) {
        write(client->fd, ERR550, strlen(ERR550));
        return (84);
    }
    write(client->fd, CDUP, strlen(CDUP));
    client->path = strdup(new_path);
    return (0);
}

int cdup(char **arr, client_t *client, server_t* server)
{
    char *new_path = my_strcat(client->path, "/..");

    if (client->status == -1) {
        write(client->fd, ERR530, strlen(ERR530));
        return (0);
    }
    if (arr[1] != NULL) {
        write(client->fd, ERR501, strlen(ERR501));
        return (84);
    }
    new_path = realpath(new_path, NULL);
    if (new_path == NULL) {
        write(client->fd, ERR431, strlen(ERR431));
        return (84);
    }
    if (strlen(new_path) > 1 && new_path[0] == '/' && new_path[1] != '\0')
        new_path = my_strcat(new_path, "/");
    return (parent_path(new_path, client, server));
}