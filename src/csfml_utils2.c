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

object create_textured_object(sfTexture *img, sfVector2f pos, sfVector2f scale)
{
    object objet;
    sfFloatRect rect;

    objet.sprite = sfSprite_create();
    objet.texture = img;
    sfSprite_setTexture(objet.sprite, objet.texture, sfFalse);
    rect = sfSprite_getGlobalBounds(objet.sprite);
    sfSprite_setOrigin(objet.sprite, VC{rect.width / 2, rect.height / 2});
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

sfVector2f utofv2(sfVector2u vector)
{
    sfVector2f result;

    result.x = vector.x;
    result.y = vector.y;
    return (result);
}
