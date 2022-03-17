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
#include "bullets.h"

int evolve_bullet(bullet_t *bullet, env_t *env)
{
    sfVector2f movement = bullet->direction;
    sfVector2f pos = sfSprite_getPosition(bullet->sprite);
    sfVector2f shooter_pos = sfSprite_getPosition(bullet->shooter->sprite);

    if (bullet->is_null == 1)
        return 0;
    movement.x *= bullet->speed;
    movement.y *= bullet->speed;
    sfSprite_move(bullet->sprite, movement);
    if (bullet_collision(bullet, env) == 1 && bullet->type != -5)
        return 1;
    if (dist_two_points(pos, shooter_pos) > bullet->shooter->range) {
        return 1;
    }
    return 0;
}

void free_bullet(bullet_t **bullet)
{
    sfSprite_destroy((*bullet)->sprite);
    free(*bullet);
}

void evolve_display_bullets(env_t *env, sfRenderWindow *win)
{
    bullet_t *actual = env->c_game.bullets;
    bullet_t *prec = env->c_game.bullets;

    while (actual != NULL) {
        if (actual->is_null == 1) {
            actual = actual->next;
            continue;
        }
        sfRenderWindow_drawSprite(win, actual->sprite, NULL);
        if (evolve_bullet(actual, env)) {
            prec->next = actual->next;
            free_bullet(&actual);
            actual = prec;
        }
        prec = actual;
        actual = actual->next;
    }
}
