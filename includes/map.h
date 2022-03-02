/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** map.h
*/

#ifndef MAP_H
    #define MAP_H

    #include "csfml.h"
    #include "structs.h"

int read_map(env_t *game, char *path);
void display_map(env_t *env);

#endif
