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

void move_rotate_enemy(enemy *mob, sfVector2f movement)
{
    sfSprite_move(mob->sprite, movement);
    if (movement.y > 0)
        sfSprite_setRotation(mob->sprite, 90);
    if (movement.y < 0)
        sfSprite_setRotation(mob->sprite, 270);
    if (movement.x > 0)
        sfSprite_setRotation(mob->sprite, 0);
    if (movement.x < 0)
        sfSprite_setRotation(mob->sprite, 180);
}

void evolve_enemy(env_t *env, enemy *mob)
{
    sfVector2f pos = sfSprite_getPosition(mob->sprite);
    sfVector2f movement = {0, 0};
    int mult = MSTIME(env->tempo) - mob->cooldown;

    if (mult < 13)
        return;
    mult = mult / 13;
    mob->cooldown = MSTIME(env->tempo);
    pos.x = pos.x - mob->offset.x - 30;
    pos.y = pos.y - mob->offset.y - 30;
    if (mob->disp.x == 0 && mob->disp.y == 0)
        point_enemy_toward_next_case(mob, pos, env);
    movement.x = (MIN(ABS(mob->disp.x), (mob->speed * mult)
        / (((mob->slowed_time > 0)) * 3 + 1)) * SIGN(mob->disp.x));
    movement.y = (MIN(ABS(mob->disp.y), (mob->speed * mult)
        / (((mob->slowed_time > 0)) * 3 + 1)) * SIGN(mob->disp.y));
    mob->disp.x -= movement.x;
    mob->disp.y -= movement.y;
    mob->slowed_time -= (mob->slowed_time > 0);
    move_rotate_enemy(mob, movement);
}
