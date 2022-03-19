/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ennemy
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"
#include "maths.h"

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

void point_enemy_toward_next_case(enemy *mob, sfVector2f pos, env_t *env)
{
    mob->age++;
    if (nextph_type == 5) {
        mob->disp.x = 512;
    } else {
        mob->disp.x = ((nextph.x * 60 > pos.x) -
            (nextph.x * 60 < pos.x)) * 60;
        mob->disp.y = ((nextph.y * 60 > pos.y) -
            (nextph.y * 60 < pos.y)) * 60;
    }
}

void evolve_enemy(env_t *env, enemy *mob)
{
    sfVector2f pos = sfSprite_getPosition(mob->sprite);
    sfVector2f movement = {0, 0};
    int mult = sfTime_asMilliseconds(sfClock_getElapsedTime(
        env->tempo)) - mob->cooldown;

    if (mult < 13)
        return;
    mult = mult / 13;
    mob->cooldown = sfTime_asMilliseconds(sfClock_getElapsedTime(env->tempo));
    pos.x = pos.x - mob->offset.x - 30;
    pos.y = pos.y - mob->offset.y - 30;
    if (mob->disp.x == 0 && mob->disp.y == 0)
        point_enemy_toward_next_case(mob, pos, env);
    movement.x = MIN(ABS(mob->disp.x), mob->speed * mult) * SIGN(mob->disp.x);
    movement.y = MIN(ABS(mob->disp.y), mob->speed * mult) * SIGN(mob->disp.y);
    mob->disp.x -= movement.x;
    mob->disp.y -= movement.y;
    sfSprite_move(mob->sprite, movement);
}

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
