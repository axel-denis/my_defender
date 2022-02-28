/*
** EPITECH PROJECT, 2021
** sokoban
** File description:
** my_strdup.c
*/

#include <stdlib.h>

int my_strlen(char const *str);

char *my_strdup(char *str)
{
    int len = my_strlen(str);
    char *output = malloc(sizeof(char) * len + 1);

    output[len] = '\0';
    for (int i = 0; i < len; i++)
        output[i] = str[i];
    return output;
}
