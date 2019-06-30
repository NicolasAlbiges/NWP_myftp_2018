/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

client_t *which_client(int fd, client_t *head, int mode)
{
    client_t *tmp = head;

    while (tmp != NULL) {
        if (mode == 0 && tmp->fd == fd)
            return (tmp);
        if (mode == 1 && tmp->fd_port == fd)
            return (tmp);
        tmp = tmp->next;
    }
    return (tmp);
}

int main(int ac, char **av)
{
    DIR* dir = NULL;

    if (error_handling_argv(ac) == 84) {
        fprintf(stderr, "USAGE: ./myftp port path\n\tport  is the port ");
        fprintf(stderr, "number on which the server socket listens\n");
        fprintf(stderr, "\tpath  is the path to the ");
        fprintf(stderr, "home directory for the Anonymous user\n");
        return (84);
    }
    if (error_handling_port(av[1]) == 84) {
        return (84);
    }
    if ((dir = opendir(av[2])) == NULL) {
        fprintf(stderr, "The path must exist.\n");
        return (84);
    }
    return (server(init_server(atoi(av[1]), av[2])));
}