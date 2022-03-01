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

map_block **read_map(env_t *game, char *path);

#endif
