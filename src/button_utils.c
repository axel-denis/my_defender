/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** button_utils
*/

#include "button.h"


void center_button_text(button *bouton)
{
    sfVector2f pos = sfSprite_getPosition((*bouton).sprite);
    sfFloatRect scale = sfSprite_getGlobalBounds((*bouton).sprite);
    sfFloatRect ownscale = sfText_getGlobalBounds((*bouton).text.text);
    int si = sfText_getCharacterSize((*bouton).text.text);

    pos = VC{pos.x + scale.width / 2 , pos.y + scale.height / 2 };
    pos = VC{pos.x - ownscale.width / 2 , pos.y - ownscale.height / 2 - si / 2};
    sfText_setPosition((*bouton).text.text, pos);
}

void button_set_position(button *bouton, sfVector2f pos)
{
    sfSprite_setPosition((*bouton).sprite, pos);
    center_button_text(bouton);
}

void display_button(sfRenderWindow *window, button bouton)
{
    sfRenderWindow_drawSprite(window, bouton.sprite, NULL);
    if (bouton.text.to_display == sfTrue)
        sfRenderWindow_drawText(window, bouton.text.text, NULL);
}
