/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** pause_menu
*/

#include "csfml.h"
#include "lib.h"
#include "menu.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"

button *create_buttons_pause(env_t *env)
{
    button *buttons = malloc(sizeof(button) * 3);
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    buttons[0] = create_button(VC{0.2, 0.2}, VC{258, WINDOW_HEIGHT / 2 - 150}, sfTrue);
    buttons[1] = create_button(VC{0.2, 0.2}, VC{258, WINDOW_HEIGHT / 2 + 50}, sfTrue);
    buttons[2] = create_button(VC{0.2, 0.2}, VC{258, WINDOW_HEIGHT / 2 + 250}, sfTrue);
    for (int i = 0; i < 3; i++) {
        setup_button_texture(&(buttons[i]), &square, "img/Blue_button.png");
        setup_button_sounds(&(buttons[i]), "sounds/click.ogg", "sounds/hover.ogg", env);
    }
    if (env->langue[0] == 'E') {
        setup_button_text(&(buttons[0]), "Resume", "font/Xero.ttf", 40);
        setup_button_text(&(buttons[1]), "Main menu", "font/Xero.ttf", 40);
        setup_button_text(&(buttons[2]), "Quit", "font/Xero.ttf", 40);
    } else {
        setup_button_text(&(buttons[0]), "Retour", "font/Xero.ttf", 40);
        setup_button_text(&(buttons[1]), "Menu principal", "font/Xero.ttf", 25);
        setup_button_text(&(buttons[2]), "Quitter", "font/Xero.ttf", 40);
    }
    for (int i = 0; i < 3; i++)
        center_button_text(&(buttons[i]));
    return (buttons);
}

int pause_menu(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    int to_return = 0;
    sfClock *clock = sfClock_create();
    button *buttons = create_buttons_pause(env);
    text texte = setup_text("   Pause", "font/o_driftbold.ttf", 150);
    object backfr = create_object("img/pause_fr.jpg", VC{0, 0}, VC{1, 1});
    object backen = create_object("img/pause_en.jpg", VC{0, 0}, VC{1, 1});

    sfText_setPosition(texte.text, VC{135, 120});
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        get_events(window, keys);
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > 1 && keys[sfKeyEscape] == 1)
            open = 0;
        if (is_pressed(buttons[0], window, keys))
            open = 0;
        if (is_pressed(buttons[1], window, keys)) {
            open = 0;
            to_return = 1;
        }
        if (is_pressed(buttons[2], window, keys))
            sfRenderWindow_close(window);
        display_background(window, backfr, backen, env);
        for (int i = 0; i < 3; i++)
            display_button(window, &(buttons[i]), keys);
        sfRenderWindow_drawText(window, texte.text, NULL);
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
    }
    for (int i = 0; i < 3; i++)
        destroy_button(buttons[i]);
    keys[sfKeyEscape] = 0;
    return to_return;
}
