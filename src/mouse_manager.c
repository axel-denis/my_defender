/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** mouse_manager
*/

#include "mouse.h"

object setup_mouse(char *filename, sfVector2f scale)
{
    object mouse;

    mouse.sprite = sfSprite_create();
    mouse.texture = sfTexture_createFromFile(filename, NULL);
    sfSprite_setScale(mouse.sprite, scale);
    sfSprite_setTexture(mouse.sprite, mouse.texture, sfFalse);
    return (mouse);
}

sfVector2f get_true_mouse_pos(sfRenderWindow *window)
{
    sfVector2f mouse_pos = itofv2(sfMouse_getPositionRenderWindow(window));
    sfVector2u screen_size = sfRenderWindow_getSize(window);

    mouse_pos.x = mouse_pos.x / screen_size.x * WINDOW_WIDTH;
    mouse_pos.y = mouse_pos.y / screen_size.y * WINDOW_HEIGHT;
    if (mouse_pos.x < 0)
        mouse_pos.x = 0;
    if (mouse_pos.y < 0)
        mouse_pos.y = 0;
    return (mouse_pos);
}

void update_mouse_cursor(sfRenderWindow *window, object mouse)
{
    sfVector2f mouse_pos = get_true_mouse_pos(window);

    sfSprite_setPosition(mouse.sprite, mouse_pos);
    sfRenderWindow_drawSprite(window, mouse.sprite, NULL);
}
