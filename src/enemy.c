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

enemy create_enemy_type_1(env_t *env)
{
    enemy template;

    template.type = 1;
    template.speed = 1;
    template.health = 100;
    template.sprite = sfSprite_create();
    sfSprite_setPosition(template.sprite, VC{env->starting_square.x * 60 + rand() % 60 - 30, env->starting_square.y * 60 + rand() % 60 - 30});
    template.texture = sfTexture_createFromFile("img/type1.png", NULL);
    sfSprite_setTexture(template.sprite, template.texture, sfFalse);
    sfSprite_setOrigin(template.sprite, VC{sfSprite_getGlobalBounds(template.sprite).width / 2, sfSprite_getGlobalBounds(template.sprite).height / 2});
    template.actual_dest.x = env->map[(int) env->starting_square.x][(int) env->starting_square.y].next_path.x * 60;
    template.actual_dest.y = env->map[(int) env->starting_square.x][(int) env->starting_square.y].next_path.y * 60;
    return template;
}

void evolve_enemy(env_t *env, enemy *mob)
{
    sfVector2f pos = sfSprite_getPosition(mob->sprite);
    sfVector2f movement = {0, 0};

    mob->actual_dest.x = env->map[(int) pos.y / 60][(int) pos.x / 60].next_path.x * 60;
    mob->actual_dest.y = env->map[(int) pos.y / 60][(int) pos.x / 60].next_path.y * 60;
    movement.x = (get_case_coords(pos).x < get_case_coords(mob->actual_dest).x) - (get_case_coords(pos).x > get_case_coords(mob->actual_dest).x);
    movement.y = (get_case_coords(pos).y < get_case_coords(mob->actual_dest).y) - (get_case_coords(pos).y > get_case_coords(mob->actual_dest).y);
    movement.x *= mob->speed;
    movement.y *= mob->speed;
    sfSprite_move(mob->sprite, movement);
}
