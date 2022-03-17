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
    precedent->next = enemy_to_remove->next;
    free(enemy_to_remove);
    return precedent->next;
}

void enemy_end_of_track(env_t *env, enemy *actual)
{
    sfVector2f pos = sfSprite_getPosition(actual->sprite);
    if (pos.x >= WINDOW_WIDTH + 15 || pos.y >= WINDOW_HEIGHT + 15) {
        env->c_game.player_stats.health -= 1;
        actual->health = 0;
    }
}
void evolve_all_enemies(env_t *env)
{
    enemy *actual = env->c_game.enemies;
    enemy *last = actual;

    if (sfTime_asMilliseconds(sfClock_getElapsedTime(env->c_game.clock)) < 13)
        return;
    while (actual != NULL) {
        if (actual->type != 0) {
            enemy_end_of_track(env, actual);
            evolve_enemy(env, actual);
            actual = remove_next_enemy_if_needed(last);
        }
        if (actual == NULL)
            return;
        last = actual;
        actual = actual->next;
    }
}

enemy *create_null_enemy(void)
{
    enemy *output = malloc(sizeof(enemy));

    output->disp = VC{0, 0};
    output->health = 1;
    output->speed = 0;
    output->sprite = NULL;
    output->texture = NULL;
    output->type = 0;
    output->next = NULL;
    return output;
}

enemy *last_e_link(enemy *first)
{
    while (first->next != NULL)
        first = first->next;
    return first;
}
