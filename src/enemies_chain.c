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

void remove_next_enemy_if_needed(enemy *precedent)
{
    enemy *enemy_to_remove = precedent->next;

    if (enemy_to_remove->next == NULL || enemy_to_remove->health > 0)
        return;
    printf("passed\n");
    precedent->next = enemy_to_remove->next;
    free(enemy_to_remove);
}

void evolve_all_enemies(env_t *env)
{
    enemy *actual = env->entities.enemies;
    enemy *last = actual;

    while (actual != NULL) {
        printf("=======\n");
        if (actual->type != 0) {
            evolve_enemy(env, actual);
            printf("enemy health : %d\n", actual->health);
            actual->health--;
            remove_next_enemy_if_needed(last);
        }
        last = actual;
        actual = actual->next;
    }
}
