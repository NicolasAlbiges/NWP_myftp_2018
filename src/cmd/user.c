/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int user(char **arr, client_t *client, UNUSED server_t* server)
{
    write(client->fd, USER, strlen(USER));
    if (arr[1] == NULL) {
        client->username = "";
        return (0);
    }
    client->username = strdup(arr[1]);
    return (0);
}