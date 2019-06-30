/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int path_handling(char **arr, client_t *client, server_t* server)
{
    char *new_path = NULL;

    new_path = realpath(my_strcat(client->path, arr[1]), NULL);
    if (new_path == NULL) {
        write(client->fd, ERR550, strlen(ERR550));
        return (84);
    }
    if (strlen(new_path) > 1 && new_path[0] == '/' && new_path[1] != '\0')
        new_path = my_strcat(new_path, "/");
    if (strlen(server->path) > strlen(new_path)) {
        write(client->fd, ERR550, strlen(ERR550));
        return (84);
    }
    client->path = strdup(my_strcat(new_path, "/"));
    write(client->fd, CWD, strlen(CWD));
    return (0);
}

int cwd(char **arr, client_t *client, server_t* server)
{
    DIR* dir = NULL;

    if (client->status == -1) {
        write(client->fd, ERR530, strlen(ERR530));
        return (84);
    }
    if (arr[1] != NULL && arr[2] == NULL) {
        if ((dir = opendir(my_strcat(client->path, arr[1]))) == NULL) {
            write(client->fd, ERR550, strlen(ERR550));
            return (84);
        }
        closedir(dir);
        return (path_handling(arr, client, server));
    } else
        write(client->fd, ERR550, strlen(ERR550));
    return (0);
}