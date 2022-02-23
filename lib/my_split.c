/*
** EPITECH PROJECT, 2021
** bsminishell1
** File description:
** split.c
*/

#include <stdlib.h>

int word_count(char *str, char separator)
{
    int result = !(str[0] == separator) || (str[0] == '\0');

    for (int i = 0; str[i]; i++) {
        if (str[i] == separator)
            result += 1;
        while (str[i] == separator)
            i++;
        if (str[i] == '\0')
            return result - 1;
    }
    return result;
}

int word_len(char *str, char endline)
{
    int result = 0;

    for (result = 0; str[result] != '\0' && str[result] != endline; result++);
    return result;
}

char **my_split(char *str, char separator)
{
    int count = word_count(str, separator);
    int offset = 0;
    int len = 0;
    char **output = malloc(sizeof(char *) * (count + 1));

    for (; str[offset] == separator; offset++);
    output[count] = NULL;
    for (int i = 0; i < count; i++) {
        len = word_len(&(str[offset]), separator);
        output[i] = malloc(sizeof(char) * (len + 1));
        for (int j = 0; j < len; j++) {
            output[i][j] = str[j + offset];
        }
        output[i][len] = '\0';
        offset += word_len(output[i], separator) + 1;
        for (; str[offset] == separator; offset++);
    }
    return output;
}
