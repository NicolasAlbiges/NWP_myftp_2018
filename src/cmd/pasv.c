/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

char *make_message_pasv(client_t *client)
{
    char *msg = "227 Entering Passive Mode (127,0,0,1,";
    int port_one = 0;
    int port_two = 0;

    port_one = client->data_port / 256;
    port_two = client->data_port - (port_one * 256);
    msg = my_strcat(msg, int_to_char(port_one));
    msg = my_strcat(msg, ",");
    msg = my_strcat(msg, int_to_char(port_two));
    msg = my_strcat(msg, ").\n");
    return (msg);
}

int pasv_error(UNUSED char **arr, client_t *client, server_t* server)
{
    if (client->status == -1) {
        write(client->fd, ERR530, strlen(ERR530));
        return (84);
    }
    if (client->fd_port != -1 || client->fd_port_client != -1) {
        kill_data_sock(client, &server->active_fd_set);
        write(client->fd, ERR550, strlen(ERR550));
        return (84);
    }
    return (0);
}

int pasv(UNUSED char **arr, client_t *client, server_t* server)
{
    char *msg = NULL;

    if (pasv_error(arr, client, server) == 84) {
        return (84);
    }
    kill_data_sock(client, &server->active_fd_set);
    if (arr[1] != NULL)
        write(client->fd, ERR501, strlen(ERR501));
    if (data_socket(server, client) == 84) {
        kill_data_sock(client, &server->active_fd_set);
        write(client->fd, ERR421, strlen(ERR421));
        return (84);
    }
    msg = make_message_pasv(client);
    write(client->fd, msg, strlen(msg));
    free(msg);
    return (0);
}