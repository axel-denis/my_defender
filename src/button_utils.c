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

sfBool is_pressed(button bouton, sfRenderWindow *window, int *keys)
{
    sfVector2f mouse_pos = get_true_mouse_pos(window);
    sfFloatRect rect = sfSprite_getGlobalBounds(bouton.sprite);

    if (pos_in_square(mouse_pos, rect) == sfTrue
    && (keys[leftMouse] == 3))
        return (sfTrue);
    return (sfFalse);
}

void button_set_position(button *bouton, sfVector2f pos)
{
    sfSprite_setPosition((*bouton).sprite, pos);
    center_button_text(bouton);
}

void display_button(sfRenderWindow *window, button *bouton, int *keys)
{
    sfVector2u size = sfTexture_getSize((*bouton).texture);
    sfVector2f mouse_pos = get_true_mouse_pos(window);
    sfFloatRect rect = sfSprite_getGlobalBounds((*bouton).sprite);

    if (pos_in_square(mouse_pos, rect) == sfFalse) {
        (*bouton).already_hoverd = 0;
        sfSprite_setTextureRect((*bouton).sprite, create_rect(0, 0, size.x / 3, size.y));
    }
    if (pos_in_square(mouse_pos, rect) == sfTrue && (*bouton).hover != NULL && (*bouton).already_hoverd == 0) {
        sfSound_play((*bouton).hover);
        (*bouton).already_hoverd = 1;
    }
    if (pos_in_square(mouse_pos, rect) == sfTrue && (keys[leftMouse] == 0 || keys[leftMouse] == 3))
        sfSprite_setTextureRect((*bouton).sprite, create_rect(size.x / 3, 0, size.x / 3, size.y));
    if (pos_in_square(mouse_pos, rect) == sfTrue && (keys[leftMouse] == 1 || keys[leftMouse] == 2))
        sfSprite_setTextureRect((*bouton).sprite, create_rect((size.x / 3) * 2 , 0, size.x / 3, size.y));
    if (pos_in_square(mouse_pos, rect) == sfTrue && keys[leftMouse] == 3)
        if ((*bouton).click != NULL)
            sfSound_play((*bouton).click);
    sfRenderWindow_drawSprite(window, (*bouton).sprite, NULL);
    if ((*bouton).text.to_display == sfTrue)
        sfRenderWindow_drawText(window, (*bouton).text.text, NULL);
}

void destroy_button(button bouton)
{
    sfSprite_destroy(bouton.sprite);
    sfTexture_destroy(bouton.texture);
    if (bouton.text.to_display == 1) {
        sfText_destroy(bouton.text.text);
        sfFont_destroy(bouton.text.font);
    }
    sfSound_stop(bouton.click);
    sfSound_stop(bouton.hover);
    sfSound_destroy(bouton.click);
    sfSound_destroy(bouton.hover);
    sfSoundBuffer_destroy(bouton.click_buf);
    sfSoundBuffer_destroy(bouton.hover_buf);
}
