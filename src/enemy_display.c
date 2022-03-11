/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** enemy_display.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"
#include "maths.h"

void display_enemies(sfRenderWindow *window, env_t *env)
{
    enemy *actual = env->c_game.enemies;

    while (actual != NULL) {
        if (actual->type != 0)
            sfRenderWindow_drawSprite(window, actual->sprite, NULL);
        actual = actual->next;
    }
}
