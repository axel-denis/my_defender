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

#define RATIO 60

void display_map(env_t *env, sfRenderWindow *window)
{
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            sfSprite_setPosition(env->map[i][j].sprite, (sfVector2f) {j * 60, i * 60});
            sfRenderWindow_drawSprite(window, env->map[i][j].sprite, NULL);
        }
        //printf("%d.", env->map[i][j].type);
        printf("\n");
    }
}
