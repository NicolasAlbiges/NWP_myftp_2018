/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int dele(char **arr, client_t *client, UNUSED server_t* server)
{
    if (client->status == -1) {
        write(client->fd, ERR530, strlen(ERR530));
        return (84);
    }
    if (arr[1] != NULL) {
        if (client->path == NULL
        || remove(my_strcat(client->path, arr[1])) == -1) {
            write(client->fd, ERR550, strlen(ERR550));
            return (84);
        }
        write(client->fd, DELE, strlen(DELE));
    } else
        write(client->fd, ERR501, strlen(ERR501));
    return (0);
}