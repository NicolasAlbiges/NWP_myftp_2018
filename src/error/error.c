/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int authentication(client_t *client)
{
    if (client->status == -1) {
        write(client->fd, ERR530, strlen(ERR530));
    }
}