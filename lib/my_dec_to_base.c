/*
** EPITECH PROJECT, 2021
** my_printf
** File description:
** decimal base to an other base
*/

#include <stdlib.h>

#include "lib.h"

static char *my_dec_to_base4(int, char *, int, int);
static char *my_dec_to_base3(int, char *, int, int);
static char *my_dec_to_base2(long, char *, int, int);

char *my_dec_to_base(long nb, char *base)
{
    int nb2 = nb;
    int i = 0;

    if (nb > 0) {
        for (i = 0; nb2 >= 1; i++)
            nb2 = nb2 / my_strlen(base);
        char *result = malloc(sizeof(char *) * (i + 1));

        for (i = 0; nb >= 1; i++) {
            result[i] = base[nb % my_strlen(base)];
            nb = nb / my_strlen(base);
        }
        result[i] = '\0';
        return (my_revstr(result));
    } else
        return (my_dec_to_base2(nb, base, i, nb2));
}

static char *my_dec_to_base2(long nb, char *base, int i, int nb2)
{
    if (nb == 0) {
        char *result = malloc(sizeof(char *) * (2));

        result[0] = base[0];
        result[1] = '\0';
        return (result);
    } else {
        return (my_dec_to_base4(nb, base, i, nb2));
    }
}

static char *my_dec_to_base4(int nb, char *base, int i, int nb2)
{
    if (nb == -2147483648)
        return (my_dec_to_base3(nb, base, i, nb2));
    nb = nb * -1;
    for (i = 0; nb2 >= 1; i++)
        nb2 = nb2 / my_strlen(base);
    char *result = malloc(sizeof(char *) * (i + 1));

    for (i = 0; nb >= 1; i++) {
        result[i] = base[nb % my_strlen(base)];
        nb = nb / my_strlen(base);
    }
    result[i] = '-';
    result[i + 1] = '\0';
    return (my_revstr(result));
}

static char *my_dec_to_base3(int nb, char *base, int i, int nb2)
{
    nb = (nb + 1) * -1;
    for (i = 0; nb2 >= 1; i++)
        nb2 = nb2 / my_strlen(base);
    char *result = malloc(sizeof(char *) * (i + 1));

    for (i = 0; nb >= 1; i++) {
        if (i == 0)
            result[i] = base[nb % my_strlen(base) + 1];
        else
            result[i] = base[nb % my_strlen(base)];
        nb = nb / my_strlen(base);
    }
    result[i] = '-';
    result[i + 1] = '\0';
    return (my_revstr(result));
}
