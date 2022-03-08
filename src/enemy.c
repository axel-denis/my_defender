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

#include <stdlib.h>

#define nextpath env->map[(int) pos.y / 60][(int) pos.x / 60].next_path

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

void create_enemy_type_1(env_t *env)
{
    enemy *actual = env->entities.enemies;

    if (actual == NULL) {
        env->entities.enemies = create_null_enemy();
        actual = env->entities.enemies;
    }
    while (actual->next != NULL)
        actual = actual->next;
    actual->next = malloc(sizeof(enemy));
    actual->next->type = 1;
    actual->next->speed = 1;
    actual->next->health = 100;
    actual->next->sprite = sfSprite_create();
    actual->next->disp = VC{0, 0};
    sfSprite_setPosition(actual->next->sprite, VC{env->starting_square.x * 60 + 30 + rand() % 30 - 15, env->starting_square.y * 60 + 30 + rand() % 30 - 15});
    actual->next->texture = sfTexture_createFromFile("img/type1.png", NULL);
    sfSprite_setTexture(actual->next->sprite, actual->next->texture, sfFalse);
    sfSprite_setOrigin(actual->next->sprite, VC{sfSprite_getGlobalBounds(actual->next->sprite).width / 2, sfSprite_getGlobalBounds(actual->next->sprite).height / 2});
    actual->next->next = NULL;
}

void evolve_enemy(env_t *env, enemy *mob)
{
    sfVector2f pos = sfSprite_getPosition(mob->sprite);
    sfVector2f movement = {0, 0};

    if (mob->disp.x == 0 && mob->disp.y == 0) {
        mob->disp.x = ((nextpath.x > get_case_coords(pos).x) - (nextpath.x < get_case_coords(pos).x));
        mob->disp.y = ((nextpath.y > get_case_coords(pos).y) - (nextpath.y < get_case_coords(pos).y));
        mob->disp.x *= 1 / mob->speed * 60;
        mob->disp.y *= 1 / mob->speed * 60;
    }

    movement.x = ((mob->disp.x > 0) - (mob->disp.x < 0)) * mob->speed;
    movement.y = ((mob->disp.y > 0) - (mob->disp.y < 0)) * mob->speed;
    mob->disp.x += ((mob->disp.x < 0) - (mob->disp.x > 0)) * mob->speed;
    mob->disp.y += ((mob->disp.y < 0) - (mob->disp.y > 0)) * mob->speed;
    sfSprite_move(mob->sprite, movement);
}
