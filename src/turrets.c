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

turret_t *template_turret(int type, int dpa, int dmg_spd)
{
    turret_t *output = malloc(sizeof(turret_t));

    output->type = type;
    output->range = 60;
    output->damage_per_action = dpa;
    output->damage_speed = dmg_spd;
    output->next = NULL;
    output->position = VC{0, 0};
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
    actual->next = template_turret(turret->type, turret->damage_per_action, turret->damage_speed);
    actual->next->damage_speed = turret->damage_speed;
    actual->next->range = turret->range;
    actual->next->sprite = sfSprite_create();
    actual->next->texture = turret->texture;
    sfSprite_setTexture(actual->next->sprite, actual->next->texture, sfFalse);
    sfSprite_setScale(actual->next->sprite, VC{.2, .2});
    sfSprite_setOrigin(actual->next->sprite, VC{150, 250});
    actual->next->position = VC{pos.x * 60 + 30, pos.y * 60 + 30};
    sfSprite_setPosition(actual->next->sprite, actual->next->position);
    actual->next->next = NULL;
    new_bullet(env, get_nearest(env, sfSprite_getPosition(actual->next->sprite)), actual->next);
}

turret_t *create_turret_1()
{
    turret_t *turret = template_turret(1, 1, 1);

    turret->sprite = sfSprite_create();
    turret->texture = sfTexture_createFromFile("img/turret1_3.png", NULL);
    sfSprite_setTexture(turret->sprite, turret->texture, sfFalse);
    sfSprite_setScale(turret->sprite, VC{.2, .2});
    sfSprite_setOrigin(turret->sprite, VC{150, 250});
    turret->position = VC{0, 0};
    turret->range = 180;
    sfSprite_setPosition(turret->sprite, turret->position);
    return turret;
}

