/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** options
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "menu.h"
#include "events.h"
#include "button.h"

void buttons_manager(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    langue_manager(but, window, keys, env);
    volume_manager(but, window, keys, env);
    volume_manager2(but, window, keys, env);
}

void display_options(sfRenderWindow *win, object mouse, button *but, int *keys)
{
    for (int i = 0; i < 5; i++)
        display_button(win, but[i], keys);
    update_mouse_cursor(win, mouse);
}

void options(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    text texte = setup_text("  Options", "font/oceanicdriftbold.ttf", 150);
    object background = create_object("img/bg.jpg", VC{0, 0}, VC{1, 1});
    button *buttons = create_buttons_options();

    setup_buttons_options(buttons, env);
    sfText_setPosition(texte.text, VC{960 - 860, WINDOW_HEIGHT / 2 - 360 - 50});
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        buttons_manager(buttons, window, keys, env);
        if (is_pressed(buttons[3], window, keys))
            open = 0;
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        sfRenderWindow_drawText(window, texte.text, NULL);
        display_options(window, mouse, buttons, keys);
        sfRenderWindow_display(window);
    }
    keys[sfKeyEscape] = 0;
}
