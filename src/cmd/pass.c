/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int pass(char **arr, client_t *client, UNUSED server_t* server)
{
    if (arr[1] == NULL) {
        client->password = "";
        if (strcmp(client->username, "Anonymous") == 0) {
            write(client->fd, PASS, strlen(PASS));
            client->status = 0;
            return (0);
        }
        write(client->fd, ERR530, strlen(ERR530));
    } else {
        client->password = strdup(arr[1]);
        client->status = -1;
        write(client->fd, ERR530, strlen(ERR530));
    }
    return (0);
}