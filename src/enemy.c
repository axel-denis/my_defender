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

enemy *template_enemy(int type, int speed, int health)
{
    enemy *output = malloc(sizeof(enemy));

    output->type = type;
    output->speed = speed;
    output->health = health;
    return output;
}

void create_enemy_type_1(env_t *env)
{
    enemy *actual = env->c_game.enemies;

    if (actual == NULL) {
        env->c_game.enemies = create_null_enemy();
        actual = env->c_game.enemies;
    }
    while (actual->next != NULL)
        actual = actual->next;
    actual->next = template_enemy(1, 1, 100);
    actual->next->sprite = sfSprite_create();
    actual->next->disp = VC{0, 0};
    sfSprite_setPosition(actual->next->sprite, VC{env->starting_square.x * 60 + 30 + rand() % 30 - 15, env->starting_square.y * 60 + 30 + rand() % 30 - 15});
    actual->next->texture = sfTexture_createFromFile("img/type1.png", NULL);
    sfSprite_setTexture(actual->next->sprite, actual->next->texture, sfFalse);
    sfSprite_setOrigin(actual->next->sprite, VC{sfSprite_getGlobalBounds(actual->next->sprite).width / 2, sfSprite_getGlobalBounds(actual->next->sprite).height / 2});
    actual->next->next = NULL;
}

void create_test_enemy(env_t *env, int health)
{
    enemy *actual = env->c_game.enemies;

    if (actual == NULL) {
        env->c_game.enemies = create_null_enemy();
        actual = env->c_game.enemies;
    }
    while (actual->next != NULL)
        actual = actual->next;
    actual->next = template_enemy(1, 1, health);
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
    int clock_mult = sfTime_asMilliseconds(sfClock_getElapsedTime(env->c_game.clock)) / 17;

    if (mob->disp.x == 0 && mob->disp.y == 0) {
        mob->disp.x = ((nextpath.x > get_case_coords(pos).x) - (nextpath.x < get_case_coords(pos).x));
        mob->disp.y = ((nextpath.y > get_case_coords(pos).y) - (nextpath.y < get_case_coords(pos).y));
        mob->disp.x *= 1 / mob->speed * 60;
        mob->disp.y *= 1 / mob->speed * 60;
    }

    movement.x = ((mob->disp.x > 0) - (mob->disp.x < 0)) * mob->speed * clock_mult;
    movement.y = ((mob->disp.y > 0) - (mob->disp.y < 0)) * mob->speed * clock_mult;
    mob->disp.x += ((mob->disp.x < 0) - (mob->disp.x > 0)) * mob->speed * clock_mult;
    mob->disp.y += ((mob->disp.y < 0) - (mob->disp.y > 0)) * mob->speed * clock_mult;
    sfSprite_move(mob->sprite, movement);
}
