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
#include "bullets.h"

turret_t *create_null_turret(void)
{
    turret_t *output = malloc(sizeof(turret_t));

    output->position = VC{0, 0};
    output->damage_per_action = 0;
    output->damage_speed = 0;
    output->sprite = NULL;
    output->texture = NULL;
    output->type = 0;
    output->next = NULL;
    return output;
}

turret_t *template_turret(turret_t *turret)
{
    turret_t *output = malloc(sizeof(turret_t));

    output->type = turret->type;
    output->range = 60;
    output->damage_per_action = turret->damage_per_action;
    output->damage_speed = turret->damage_speed;
    output->next = NULL;
    output->position = VC{0, 0};
    output->name = turret->name;
    output->energy_cost = turret->energy_cost;
    output->steel_cost = turret->steel_cost;
    output->energy_per_s = turret->energy_per_s;
    output->steel_per_s = turret->steel_per_s;
    output->is_base = turret->is_base;
    output->upgrade_1 = turret->upgrade_1;
    output->upgrade_2 = turret->upgrade_2;
    return output;
}

void clone_turret(env_t *env, turret_t *turret, sfVector2f pos)
{
    turret_t *actual = env->c_game.turrets;

    if (actual == NULL) {
        env->c_game.turrets = create_null_turret();
        actual = env->c_game.turrets;
    }
    while (actual->next != NULL)
        actual = actual->next;
    actual->next = template_turret(turret);
    actual->next->damage_speed = turret->damage_speed;
    actual->next->range = turret->range;
    actual->next->sprite = sfSprite_create();
    actual->next->texture = turret->texture;
    sfSprite_setTexture(actual->next->sprite, actual->next->texture, sfFalse);
    sfSprite_setScale(actual->next->sprite, VC{.9, .9});
    sfSprite_setOrigin(actual->next->sprite, VC{40, 25});
    actual->next->position = VC{pos.x * 60 + 30, pos.y * 60 + 30};
    sfSprite_setPosition(actual->next->sprite, actual->next->position);
    actual->next->cooldown = 0;
    new_bullet(env, get_oldest(env, actual->next), actual->next);
}

