/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** turrets_reader c
*/

#include <stdio.h>
#include "csfml.h"
#include "structs.h"

turret_t *load_t_inventory(char *filepath)
{
    FILE *fd = fopen(filepath, "r");
    int len = 0;
    char *buffer = NULL;
    int turret_nb = 0;

    get_turret_nb(fd, len, buffer);
}
