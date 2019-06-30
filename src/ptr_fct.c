/*
** EPITECH PROJECT, 2019
** ptr_fct.c
** File description:
** myftp
*/

#include "main.h"

int pointer_fct(char **arr, client_t *client, server_t *server)
{
    command_t const arr_cmd[14] = {{"USER", user}, {"PASS", pass},
    {"CWD", cwd},
    {"CDUP", cdup}, {"QUIT", quit}, {"DELE", dele}, {"PWD", pwd},
    {"PASV", pasv}, {"PORT", port}, {"NOOP", noop}, {"HELP", help},
    {"RETR", retr}, {"STOR", stor}, {"LIST", list}};

    if (arr == NULL || arr[0] == NULL) {
        write(client->fd, ERR500, strlen(ERR500));
        return (0);
    }
    for (int ct = 0; ct != 14; ct ++) {
        if (strcmp(arr[0], arr_cmd[ct].cmd) == 0) {
            (arr_cmd[ct].cmd_name)(arr, client, server);
            return (0);
        }
    }
    write(client->fd, ERR500, strlen(ERR500));
    return (0);
}