/*
** EPITECH PROJECT, 2019
** wordarray.c
** File description:
** myftp
*/

#include "main.h"

char **fill_arr(char **arr, char *str, char **operators)
{
    int ct = 0;
    int ct_arr = 0;
    int ct_str = 0;

    pass_key(str, &ct, operators);
    while (str[ct] != '\0') {
        if (is_operator(str[ct], operators) == 1) {
            arr[ct_arr][ct_str] = '\0';
            ct_str = 0;
            ct_arr ++;
            pass_key(str, &ct, operators);
        } else {
            arr[ct_arr][ct_str] = str[ct];
            ct_str ++;
            ct ++;
        }
    }
    if (ct_str > 0)
        arr[ct_arr][ct_str] = '\0';
    return (arr);
}

char **malloc_arr(char **arr, char *str, char **operators)
{
    int ct = 0;
    int len = 0;
    int ct_arr = 0;

    pass_key(str, &ct, operators);
    while (str[ct] != '\0') {
        if (is_operator(str[ct], operators) == 1) {
            arr[ct_arr] = malloc(sizeof(char) * (len + 1));
            ct_arr ++;
            len = 0;
            pass_key(str, &ct, operators);
        } else {
            len ++;
            ct ++;
        }
    }
    if (len > 0)
        arr[ct_arr] = malloc(sizeof(char) * (len + 1));
    return (arr);
}

int len_arr(char *str, char **operators)
{
    int ct = 0;
    int len = 1;

    while (str[ct] != '\0' && is_operator(str[ct], operators) == 1)
        ct ++;
    while (str[ct] != '\0') {
        if (is_operator(str[ct], operators) == 1) {
            pass_key_len(str, &ct, operators, &len);
        } else
            ct ++;
    }
    return (len);
}

int empty_str(char *str, char **operators)
{
    if (strlen(str) == 0)
        return (0);
    for (int ct = 0; str[ct] != '\0'; ct ++)
        if (is_operator(str[ct], operators) == 0)
            return (1);
    return (0);
}

char **word_array(char *str, char **operators)
{
    char **arr;

    if (str == NULL || empty_str(str, operators) == 0)
        return (NULL);
    arr = malloc(sizeof(char *) * (len_arr(str, operators) + 1));
    arr = malloc_arr(arr, str, operators);
    arr = fill_arr(arr, str, operators);
    arr[len_arr(str, operators)] = NULL;
    return (arr);
}
