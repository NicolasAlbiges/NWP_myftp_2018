/*
** EPITECH PROJECT, 2019
** tools.c
** File description:
** myftp
*/

#include "main.h"

int is_operator(char c, char **operators)
{
    for (int ct = 0; operators[ct] != NULL; ct ++)
        if (c == operators[ct][0])
            return (1);
    return (0);
}

void pass_key(char *str, int *ct, char **operators)
{
    while (str[*ct] != '\0' && is_operator(str[*ct], operators) == 1)
        (*ct) ++;
}

void pass_key_len(char *str, int *ct, char **operators, int *len)
{
    while (str[*ct] != '\0' && is_operator(str[*ct], operators) == 1)
        (*ct) ++;
    if (str[*ct] != '\0')
        (*len) ++;
}

char *my_getline(FILE *stream)
{
    size_t size = 0;
    char *str = NULL;
    int readed = 0;

    readed = getline(&str, &size, stream);
    if (readed <= 0) {
        free(str);
        return (NULL);
    }
    str[readed - 1] = '\0';
    return (str);
}

char *my_getline_file(FILE *stream)
{
    size_t size = 0;
    char *str = NULL;
    int readed = 0;

    readed = getline(&str, &size, stream);
    if (readed <= 0) {
        free(str);
        return (NULL);
    }
    str[readed] = '\0';
    return (str);
}