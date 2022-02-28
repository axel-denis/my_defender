/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** mouse_manager
*/

#include "mouse.h"

object setup_button(char *filename, sfVector2f scale)
{
    object mouse;

    mouse.sprite = sfSprite_create();
    mouse.texture = sfTexture_createFromFile(filename, NULL);
    sfSprite_setScale(mouse.sprite, scale);
    sfSprite_setTexture(mouse.sprite, mouse.texture, sfFalse);
    return (mouse);
}

void update_mouse_cursor(sfRenderWindow *window, object mouse)
{
    sfVector2f mouse_pos = itofv2(sfMouse_getPositionRenderWindow(window));

    sfSprite_setPosition(mouse.sprite, mouse_pos);
    sfRenderWindow_drawSprite(window, mouse.sprite, NULL);
}
