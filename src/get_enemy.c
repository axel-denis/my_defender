/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** get_enemy.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"
#include "maths.h"

enemy *get_oldest(env_t *env, turret_t *turret)
{
    enemy *actual = env->c_game.enemies;
    enemy *output = NULL;
    sfVector2f pos = sfSprite_getPosition(turret->sprite);
    sfVector2f act_pos;
    int age = -1;

    while (actual != NULL) {
        if (actual->type == 0) {
            actual = actual->next;
            continue;
        }
        act_pos = sfSprite_getPosition(actual->sprite);
        if (dist_two_points(act_pos, pos) < turret->range
            && actual->age > age) {
            age = actual->age;
            output = actual;
        }
        actual = actual->next;
    }
    return output;
}

enemy *get_nearest(env_t *env, turret_t *turret)
{
    enemy *actual = env->c_game.enemies;
    enemy *output = NULL;
    sfVector2f pos = sfSprite_getPosition(turret->sprite);
    int act_dist;
    int dist = 2000;

    while (actual != NULL) {
        if (actual->type == 0) {
            actual = actual->next;
            continue;
        }
        act_dist = dist_two_points(sfSprite_getPosition(actual->sprite), pos);
        if (act_dist < turret->range && act_dist < dist) {
            dist = act_dist;
            output = actual;
        }
        actual = actual->next;
    }
    return output;
}
