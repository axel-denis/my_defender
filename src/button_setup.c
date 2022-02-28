/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** button_utils2
*/

#include "button.h"

button create_button(sfVector2f size, sfVector2f position, sfBool display_text)
{
    button bouton;

    bouton.is_clicked = sfFalse;
    bouton.is_hovered = sfFalse;
    bouton.text.to_display = display_text;
    bouton.sprite = sfSprite_create();
    sfSprite_setPosition(bouton.sprite, position);
    sfSprite_setScale(bouton.sprite, size);
    return (bouton);
}

void setup_button_texture(button *bouton, sfIntRect *size, char *file_name)
{
    (*bouton).texture = sfTexture_createFromFile(file_name, NULL);
    sfSprite_setTexture((*bouton).sprite, (*bouton).texture, sfFalse);
    sfSprite_setTextureRect((*bouton).sprite, *size);
}

void setup_button_text(button *bouton, char *string, char *font, int char_size)
{
    (*bouton).text.text = sfText_create();
    (*bouton).text.font = sfFont_createFromFile(font);
    sfText_setFont((*bouton).text.text, (*bouton).text.font);
    sfText_setString((*bouton).text.text, string);
    sfText_setCharacterSize((*bouton).text.text, char_size);
    center_button_text(bouton);
}
