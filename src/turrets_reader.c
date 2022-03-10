/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** turrets_reader.c
*/

#include <stdio.h>
#include "csfml.h"
#include "structs.h"

//move ce define dans un .h une fois fini
#define info_per_turret 4

int get_turret_nb(FILE *fd, int len, char *buffer)
{
    getline(&buffer, &len, fd);
    while (buffer[0] != '#') {
        free(buffer);
        getline(&buffer, &len, fd);
    }
    free(buffer);
    getline(&buffer, &len, fd);
    //prendre le nombre sous le commentaire
}

turret_t *load_t_inventory(char *filepath)
{
    FILE *fd = fopen(filepath, "r");
    int len = 0;
    char *buffer = NULL;
    int turret_nb = 0;

    get_turret_nb(fd, len, buffer);
}
