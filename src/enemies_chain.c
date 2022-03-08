/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** enemies_chain.C
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"

void evolve_all_enemies(env_t *env)
{
    enemy *actual = env->entities.enemies;

    while (actual != NULL) {
        if (actual->type != 0)
            evolve_enemy(env, actual);
        actual = actual->next;
    }
}
