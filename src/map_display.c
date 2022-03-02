/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** map_reader.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"

void display_map(env_t *env)
{
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++)
            printf("%d.", env->map[i][j].type);
        printf("\n");
    }
}
