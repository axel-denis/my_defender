/*
** EPITECH PROJECT, 2021
** lib
** File description:
** dec_to_base.c
*/

#include <stdlib.h>

char *fill_text(char const *text)
{
    int i = 0;
    int j = 0;
    char *str;

    for (; text[j]; j++);
    str = malloc(sizeof(char) * (j + 1));
    while (i != j) {
        str[i] = text[i];
        i++;
    }
    str[i] = '\0';
    return str;
}

char *dec_to_base(unsigned int dec, int base, int maj)
{
    char *result = malloc(60);
    int temp_result = 0;
    char *output;
    int count = 58;

    result[59] = '\0';
    while (dec > 0) {
        temp_result = dec % base;
        if (temp_result >= 10 && maj == 0)
            result[count] = temp_result - 10 + 'a';
        else if (temp_result >= 10 && maj == 1)
            result[count] = temp_result - 10 + 'A';
        else
            result[count] = temp_result + '0';
        dec /= base;
        count--;
    }
    output = fill_text(result + count + 1);
    free(result);
    return output;
}
