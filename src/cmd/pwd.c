/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int pwd(UNUSED char **arr, client_t *client, UNUSED server_t* server)
{
    char *pwd = "257 ";

    if (client->status == -1) {
        write(client->fd, ERR530, strlen(ERR530));
        return (84);
    }
    if (client->path != NULL) {
        pwd = my_strcat(strdup(pwd), client->path);
        pwd = my_strcat(pwd, " created.\n");
        write(client->fd, pwd, strlen(pwd));
    }
    return (0);
}