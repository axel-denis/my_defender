/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** csfml_utils
*/

#include "csfml.h"
#include "structs.h"

sfIntRect create_rect(int left, int top, int width, int height)
{
    sfIntRect rect;

    rect.left = left;
    rect.top = top;
    rect.width = width;
    rect.height = height;
    return (rect);
}

sfVector2f itofv2(sfVector2i vector)
{
    sfVector2f result;

    result.x = vector.x;
    result.y = vector.y;
    return (result);
}

sfBool pos_in_square(sfVector2f pos, sfFloatRect rect)
{
    if (pos.x > rect.left && pos.x < rect.left + rect.width)
        if (pos.y > rect.top && pos.y < rect.top + rect.height)
            return (sfTrue);
    return (sfFalse);
}

void destroy_object(object object)
{
    sfSprite_destroy(object.sprite);
    sfTexture_destroy(object.texture);
}

text setup_text(char *string, char *font, int char_size)
{
    text texte;

    texte.text = sfText_create();
    texte.font = sfFont_createFromFile(font);
    sfText_setFont(texte.text, texte.font);
    sfText_setString(texte.text, string);
    sfText_setCharacterSize(texte.text, char_size);
    return (texte);
}
