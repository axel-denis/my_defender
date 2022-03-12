/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** bullets.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"
#include "maths.h"

void display_bullets(sfRenderWindow *window, env_t *env)
{
    bullet_t *actual = env->c_game.bullets;

    while (actual != NULL) {
        if (actual->is_null != 0)
            sfRenderWindow_drawSprite(window, actual->sprite, NULL);
        actual = actual->next;
    }
}
