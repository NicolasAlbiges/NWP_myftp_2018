/*
** EPITECH PROJECT, 2019
** error_handling.c
** File description:
** myftp
*/

#include "main.h"

int error_handling_argv(int ac)
{
    if (ac == 1) {
        fprintf(stderr, "Not enought argument\n\n");
        return (84);
    }
    if (ac > 3) {
        fprintf(stderr, "Too much arguments\n\n");
        return (84);
    }
    if (ac != 3) {
        return (84);
    }
    return (0);
}

int error_handling_port(char *port)
{
    for (int ct = 0; port[ct] != '\0'; ct ++) {
        if (!isdigit(port[ct])) {
            fprintf(stderr, "Port must be a number\n");
            return (84);
        }
    }
    return (0);
}