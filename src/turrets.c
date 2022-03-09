/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** turrets.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"

turret *create_null_turret(void)
{
    turret *output = malloc(sizeof(turret));

    output->position = VC{0, 0};
    output->damage_per_action = 0;
    output->damage_speed = 0;
    output->sprite = NULL;
    output->texture = NULL;
    output->type = 0;
    output->next = NULL;
    return output;
}

turret *template_turret(int type, int dpa, int dmg_spd)
{
    turret *output = malloc(sizeof(turret));

    output->type = 1;
    output->damage_per_action = dpa;
    output->damage_speed = dmg_spd;
    output->next = NULL;
    output->position = VC{0, 0};
    return output;
}

void create_turret_1(env_t *env)
{
    turret *actual = env->c_game.turrets;

    if (actual == NULL) {
        env->c_game.turrets = create_null_turret();
        actual = env->c_game.turrets;
    }
    while (actual->next != NULL)
        actual = actual->next;
    actual->next = template_turret(1, 1, 1);
    actual->next->sprite = sfSprite_create();
    actual->next->texture = sfTexture_createFromFile("img/turret1_3.png", NULL);
    sfSprite_setTexture(actual->next->sprite, actual->next->texture, sfFalse);
    sfSprite_setScale(actual->next->sprite, VC{.2, .2});
    sfSprite_setOrigin(actual->next->sprite, VC{150, 250});
    actual->next->position = VC{60 * 5 + 30, 60 * 5 + 30};
    sfSprite_setPosition(actual->next->sprite, actual->next->position);
}

