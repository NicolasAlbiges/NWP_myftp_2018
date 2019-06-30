/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

char *help_cmd(char *cmd, char *msg)
{
    char *help[] = {"USER", "PASS", "CWD", "CDUP", "QUIT", "NOOP", "DELE",
    "PWD", "PASV", "PORT", "HELP", "RETR", "STOR", "LIST", NULL};
    char *help_msg[] = {" : Specify user for authentication\n",
    " : Specify password for authentication\n",
    " : Change working directory\n",
    " : Change working directory to parent directory\n", " : Disconnection\n",
    " : Do nothing\n", " : Delete file on the server\n",
    " : Print working directory\n",
    " : Enable 'passive' mode for data transfer\n",
    " : Enable 'active' mode for data transfer\n",
    " : List available commands\n",
    " : Download file from server to client\n",
    " : Upload file from client to server\n, ",
    " : List files in the current working directory\n", NULL};

    for (int ct = 0; help[ct] != NULL; ct ++)
        if (strcmp(cmd, help[ct]) == 0) {
            msg = my_strcat(msg, help[ct]);
            msg = my_strcat(msg, help_msg[ct]);
        }
    return (msg);
}

int help(char **arr, client_t *client, UNUSED server_t* server)
{
    char *msg = "214 ";

    if (arr[1] != NULL) {
        for (int ct = 1; arr[ct] != NULL; ct ++)
            msg = help_cmd(arr[ct], msg);
        msg = my_strcat(msg, " created.\n");
        write(client->fd, msg, strlen(msg));
    } else
        write(client->fd, HELP, strlen(HELP));
    return (0);
}