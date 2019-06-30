/*
** EPITECH PROJECT, 2019
** int_to_char.c
** File description:
** myftp
*/

#include "main.h"

char *my_revstr_int_to_char(char *str)
{
    char *tmp = malloc(sizeof(char) * (strlen(str) + 1));
    int i = strlen(str) - 1;
    int w = 0;

    if (str[0] == '-') {
        tmp[0] = '-';
        w ++;
    }
    while (i > -1) {
        if (str[i] == '-')
            break;
        tmp[w] = str[i];
        w = w + 1;
        i = i - 1;
    }
    free(str);
    tmp[w] = '\0';
    return (tmp);
}

int len_nb(int nb)
{
    int i = 0;

    if (nb == 0)
        return (1);
    if (nb < 0) {
        nb = -nb;
        i = i + 1;
    }
    while (nb > 0) {
        nb = nb / 10;
        i = i + 1;
    }
    return (i);
}

char *int_to_char(int nb)
{
    char *str = malloc(sizeof(char) * len_nb(nb) + 1);
    int ct = 0;

    if (nb == 0)
        return ("0");
    if (nb < 0) {
        nb = -nb;
        str[0] = '-';
        ct ++;
    }
    while (nb > 0) {
        str[ct] = (nb % 10) + 48;
        nb = nb / 10;
        ct ++;
    }
    str[ct] = '\0';
    str = my_revstr_int_to_char(str);
    return (str);
}
