/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int error_argv(char **arr_pasv, int *port_one, int *port_two)
{
    int len = 0;

    for (int ct = 1; arr_pasv[ct] != NULL; ct ++)
        len ++;
    if (len != 6)
        return (84);
    if (((*port_one) = atoi(arr_pasv[5])) && ((*port_two) = atoi(arr_pasv[6])))
        return (0);
    else
        return (84);
    return (0);
}

void init_data_socket(client_t *client, char **arr_pasv,
int port_one, int port_two)
{
    client->adress_port = my_strcat(strdup(arr_pasv[1]), ".");
    for (int ct = 2; ct != 4; ct ++) {
        client->adress_port = my_strcat(client->adress_port, arr_pasv[ct]);
        client->adress_port = my_strcat(client->adress_port, ".");
    }
    client->adress_port = my_strcat(client->adress_port, arr_pasv[4]);
    client->data_port = (port_one * 256) + port_two;
}

int connect_data_socket(client_t *client, server_t* server)
{
    if ((client->fd_port_client = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return (84);
    client->data_sock_addr.sin_port = htons(client->data_port);
    client->data_sock_addr.sin_addr.s_addr = inet_addr(client->adress_port);
    client->data_sock_addr.sin_family = AF_INET;
    if (connect(client->fd_port_client,
    (struct sockaddr *)&client->data_sock_addr,
    sizeof(struct sockaddr_in)) == -1) {
        fprintf(stderr, "Connect PORT failed.\n");
        kill_data_sock(client, &server->active_fd_set);
        write(client->fd, ERR421, strlen(ERR421));
        return (84);
    }
    client->fd_port = -2;
    write(client->fd, CDUP, strlen(CDUP));
    return (0);
}

int port(char **arr, client_t *client, server_t* server)
{
    char *operator[] = {" ", "\t", "\r", "\n", "(", ")", ",", NULL};
    char **arr_pasv = word_array(client->cmd, operator);
    int port_one = 0;
    int port_two = 0;

    if (client->status == -1) {
        write(client->fd, ERR530, strlen(ERR530));
        return (84);
    }
    if (client->fd_port != -1 && client->fd_port_client != -1) {
        kill_data_sock(client, &server->active_fd_set);
        write(client->fd, ERR550, strlen(ERR550));
        return (84);
    }
    kill_data_sock(client, &server->active_fd_set);
    if (arr[1] == NULL || error_argv(arr_pasv, &port_one, &port_two) == 84) {
        write(client->fd, ERR501, strlen(ERR501));
        return (84);
    }
    init_data_socket(client, arr_pasv, port_one, port_two);
    return (connect_data_socket(client, server));
}