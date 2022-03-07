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

enemy create_enemy_type_1(env_t *env)
{
    enemy template;

    template.type = 1;
    template.speed = 1;
    template.health = 100;
    template.sprite = sfSprite_create();
    template.disp = VC{0, 0};
    sfSprite_setPosition(template.sprite, VC{env->starting_square.x * 60 + 30 + rand() % 30 - 15, env->starting_square.y * 60 + 30 + rand() % 30 - 15});
    template.texture = sfTexture_createFromFile("img/type1.png", NULL);
    sfSprite_setTexture(template.sprite, template.texture, sfFalse);
    sfSprite_setOrigin(template.sprite, VC{sfSprite_getGlobalBounds(template.sprite).width / 2, sfSprite_getGlobalBounds(template.sprite).height / 2});
    return template;
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
