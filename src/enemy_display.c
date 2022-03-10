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

void display_turrets(sfRenderWindow *window, env_t *env)
{
    turret_t *actual = env->c_game.turrets;
    enemy *nearest = NULL;
    sfVector2f near_pos = {0, 1};
    sfVector2f pos = {0, 0};

    while (actual != NULL) {
        if (actual->type == 0) {
            actual = actual->next;
            continue;
        }
        printf("drawed\n");
        nearest = get_nearest(env, sfSprite_getPosition(actual->sprite));
        pos = sfSprite_getPosition(actual->sprite);
        if (nearest != NULL) {
            near_pos = sfSprite_getPosition(nearest->sprite);
            sfSprite_setRotation(actual->sprite, A_regarde_B(pos, near_pos));
        }
        printf("(%f %f) to (%f %f) = %f\n", pos.x, pos.y, near_pos.x, near_pos.y, A_regarde_B(pos, near_pos));
        printf("x: %f y: %f scaleX:%f scaleY:%f\n", sfSprite_getPosition(actual->sprite).x, sfSprite_getPosition(actual->sprite).y, sfSprite_getScale(actual->sprite).x, sfSprite_getScale(actual->sprite).y);
        sfRenderWindow_drawSprite(window, actual->sprite, NULL);
        actual = actual->next;
    }
    printf("========\n");
}
