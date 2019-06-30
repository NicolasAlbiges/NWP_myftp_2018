/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int noop(UNUSED char **arr, client_t *client, UNUSED server_t* server)
{
    if (client->status == -1) {
        write(client->fd, ERR530, strlen(ERR530));
        return (84);
    }
    write(client->fd, OKAY, strlen(OKAY));
    return (0);
}