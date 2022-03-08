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
    sfMusic_setVolume(env->data.music, env->volume / 2);
}

void display_options(sfRenderWindow *win, object mouse, button *but, int *keys)
{
    center_button_text(&(but[4]));
    for (int i = 0; i < 5; i++)
        display_button(win, &(but[i]), keys);
    update_mouse_cursor(win, mouse);
}

void display_background(sfRenderWindow *win, object fr, object en, env_t *env)
{
    if (env->langue[0] == 'F')
        sfRenderWindow_drawSprite(win, fr.sprite, NULL);
    else
        sfRenderWindow_drawSprite(win, en.sprite, NULL);
}

void options(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    text texte = setup_text("  Options", "font/o_driftbold.ttf", 150);
    object backfr = create_object("img/options_fr.jpg", VC{0, 0}, VC{1, 1});
    object backen = create_object("img/options_en.jpg", VC{0, 0}, VC{1, 1});
    button *buttons = create_buttons_options(env);

    setup_buttons_options(buttons, env);
    sfText_setPosition(texte.text, VC{960 - 860, WINDOW_HEIGHT / 2 - 360 - 50});
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        buttons_manager(buttons, window, keys, env);
        if (is_pressed(buttons[3], window, keys))
            open = 0;
        display_background(window, backfr, backen, env);
        sfRenderWindow_drawText(window, texte.text, NULL);
        display_options(window, mouse, buttons, keys);
        sfRenderWindow_display(window);
    }
    for (int i = 0; i < 5; i++)
        destroy_button(buttons[i]);
    keys[sfKeyEscape] = 0;
}
