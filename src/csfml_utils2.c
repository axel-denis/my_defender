/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** csfml_utils2
*/

#include "csfml.h"
#include "structs.h"

object create_object(char *file, sfVector2f pos, sfVector2f scale)
{
    object objet;

    objet.sprite = sfSprite_create();
    objet.texture = sfTexture_createFromFile(file, NULL);
    sfSprite_setTexture(objet.sprite, objet.texture, sfFalse);
    sfSprite_setScale(objet.sprite, scale);
    sfSprite_setPosition(objet.sprite, pos);
    return (objet);
}

sfVector2i ftoiv2(sfVector2f vector)
{
    sfVector2i result;

    result.x = vector.x;
    result.y = vector.y;
    return (result);
}
