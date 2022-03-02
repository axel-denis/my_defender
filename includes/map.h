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

    #define REAL_MAP_LEN 193 // je compte 192 pourtant, étrange
    #define MAP_LEN 32
    #define MAP_HEIGHT 18
    #define SPRITE_SCALE (sfVector2f) {3.75, 3.75}
    #define DATABLOCK 6

int read_map(env_t *game, char *path);
void setmap_opacity(env_t *env, sfRenderWindow *window);
void display_map(env_t *env, sfRenderWindow *window);
sfSprite *get_case_from_mouse(env_t *env, sfVector2f mouse_pos);
sfVector2i get_case_coords(sfVector2f position);

#endif
