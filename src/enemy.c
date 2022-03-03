/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ennemy
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"

enemy create_enemy_type_1(int case_x, int case_y)
{
    enemy template;
    template.type = 1;
    template.sprite = sfSprite_create();
    template.texture = sfTexture_createFromFile("img/type1.png");
    sfSprite_setTexture(template.sprite, template.texture, sfFalse);
    template.cas
    return template;
}
