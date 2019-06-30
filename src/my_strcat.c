/*
** EPITECH PROJECT, 2017
** my_strcat
** File description:
** task02
*/

#include <main.h>

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int d = 0;
    char *tmp = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));

    while (dest[d] != '\0') {
        tmp[d] = dest[d];
        d = d + 1;
    }
    while (src[i] != '\0') {
        tmp[d] = src[i];
        i = i + 1;
        d = d + 1;
    }
    tmp[d] = '\0';
    return (tmp);
}
