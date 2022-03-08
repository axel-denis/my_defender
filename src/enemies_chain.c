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

enemy *remove_next_enemy_if_needed(enemy *precedent)
{
    enemy *enemy_to_remove = precedent->next;

    if (enemy_to_remove->health > 0)
        return enemy_to_remove;
    printf("passed\n");
    precedent->next = enemy_to_remove->next;
    free(enemy_to_remove);
    return precedent->next;
}

void evolve_all_enemies(env_t *env)
{
    printf("entry\n");
    enemy *actual = env->entities.enemies;
    enemy *last = actual;

    while (actual != NULL) {
        printf("=======\n");
        if (actual->type != 0) {
            evolve_enemy(env, actual);
            printf("enemy health : %d\n", actual->health);
            actual->health--;
            actual = remove_next_enemy_if_needed(last);
        }
        if (actual == NULL) {
            printf("returned\n");
            return;
        }
        last = actual;
        actual = actual->next;
        printf("pased and passed\n");
    }
}
