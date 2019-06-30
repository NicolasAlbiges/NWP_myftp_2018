/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int quit(UNUSED char **arr, client_t *client, UNUSED server_t* server)
{
    write(client->fd, QUIT, strlen(QUIT));
    client->status = 1;
    return (0);
}