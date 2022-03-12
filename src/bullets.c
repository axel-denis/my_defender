/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** bullets.c
*/

#include "csfml.h"
#include "structs.h"
#include "map.h"
#include "maths.h"

bullet_t *null_bullet(void)
{
    bullet_t *output = malloc(sizeof(bullet_t));

    output->is_null = 1;
    output->speed = 0;
    output->damage = 0;
    output->target = NULL;
    output->shooter = NULL;
    output->direction = VC{0, 0};
    output->sprite = NULL;
    output->next = NULL;
    return output;
}

bullet_t *create_bullet(enemy *target, turret_t *shooter)
{
    bullet_t *output = malloc(sizeof(bullet_t));
    sfVector2f target_pos = sfSprite_getPosition(target->sprite);
    sfVector2f shooter_pos = sfSprite_getPosition(shooter->sprite);
    float angle = A_regarde_B(shooter_pos, target_pos);
    sfVector2f direction = {cos(angle * (2) * M_PI / 360), sin(angle * (2) * M_PI / 360)};

    output->direction = direction;
    output->target = target;
    output->shooter = shooter;
    output->is_null = 0;
    output->speed = 15;
    output->damage = 5;
    output->sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile("img/base_arrow.png", NULL);
    sfSprite_setTexture(output->sprite, texture, sfFalse); //OPTIMIZE THIS SHIT, DON'T WANT TO PAY FOR THE CRIME OF LOADING IT AT EACH TIME
    sfSprite_setPosition(output->sprite, shooter_pos);
    sfSprite_setScale(output->sprite, VC{.1, .1});
    sfSprite_setRotation(output->sprite, angle);
    output->next = NULL;
    return output;
}

void new_bullet(env_t *env, enemy *target, turret_t *shooter)
{
    bullet_t *actual = env->c_game.bullets;

    if (actual == NULL) {
        env->c_game.bullets = null_bullet();
        actual = env->c_game.bullets;
    }
    while (actual->next != NULL) {
        actual = actual->next;
    }
    actual->next = create_bullet(target, shooter);
}
