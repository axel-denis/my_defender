/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** button_utils
*/

#include "button.h"
#include "mouse.h"

void center_button_text(button *bouton)
{
    sfVector2f pos = sfSprite_getPosition((*bouton).sprite);
    sfFloatRect scale = sfSprite_getGlobalBounds((*bouton).sprite);
    sfFloatRect ownscale = sfText_getGlobalBounds((*bouton).text.text);

    pos = VC{pos.x + scale.width / 2 , pos.y + scale.height / 2};
    pos = VC{pos.x - ownscale.width / 2 , pos.y - ownscale.height};
    sfText_setPosition((*bouton).text.text, pos);
}

void button_set_position(button *bouton, sfVector2f pos)
{
    sfSprite_setPosition((*bouton).sprite, pos);
    center_button_text(bouton);
}

void display_button(sfRenderWindow *window, button bouton)
{
    sfVector2u size = sfTexture_getSize(bouton.texture);
    sfVector2f mouse_pos = get_true_mouse_pos(window);

    sfSprite_setTextureRect(bouton.sprite, create_rect(0, 0, size.x / 3, size.y));
/*     if (bouton.is_hovered == sfTrue && bouton.is_clicked == sfFalse)
        sfSprite_setTextureRect(bouton.sprite, create_rect(size.x / 3, 0, size.x / 3, size.y));
    if (bouton.is_clicked == sfTrue)
        sfSprite_setTextureRect(bouton.sprite, create_rect((size.x / 3) * 2 , 0, size.x / 3, size.y)); */
    sfRenderWindow_drawSprite(window, bouton.sprite, NULL);
    if (bouton.text.to_display == sfTrue)
        sfRenderWindow_drawText(window, bouton.text.text, NULL);
}
