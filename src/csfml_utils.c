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

void setup_text(char *string, char *font, int char_size)
{
    text text;

    text.text = sfText_create();
    text.font = sfFont_createFromFile(font);
    sfText_setFont(text.text, text.font);
    sfText_setString(text.text, string);
    sfText_setCharacterSize(text.text, char_size);
    return (text);
}
