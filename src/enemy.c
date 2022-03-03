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

#include <stdlib.h>

enemy create_enemy_type_1(env_t *env)
{
    enemy template;
    template.type = 1;
    template.speed = 1;
    template.health = 100;
    template.sprite = sfSprite_create();
    sfSprite_setPosition(template.sprite, VC{env->starting_square.x * 60 + rand() % 30, env->starting_square.y * 60 + rand() % 30});
    template.texture = sfTexture_createFromFile("img/type1.png", NULL);
    sfSprite_setTexture(template.sprite, template.texture, sfFalse);
    return template;
}
