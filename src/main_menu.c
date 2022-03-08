/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Espace de travail)
** File description:
** main_menu
*/

#include "csfml.h"
#include "lib.h"
#include "menu.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"

void change_button_text(button *buttons, env_t *env)
{
    if (env->langue[0] == 'E') {
        sfText_setString(buttons[0].text.text, "Start");
        sfText_setString(buttons[1].text.text, "Options");
        sfText_setString(buttons[2].text.text, "Quit");
    } else {
        sfText_setString(buttons[0].text.text, "Demarrer");
        sfText_setString(buttons[1].text.text, "Options");
        sfText_setString(buttons[2].text.text, "Quitter");
    }
    for (int i = 0; i < 3; i ++)
        center_button_text(&(buttons[i]));
}

button *create_buttons_menu(void)
{
    button *buttons = malloc(sizeof(button) * 3);
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    buttons[0] = create_button(VC{0.2, 0.2}, VC{WINDOW_WIDTH / 2 - ((6065 / 3) / 2) * 0.2 + 500, WINDOW_HEIGHT / 2 - 150}, sfTrue);
    buttons[1] = create_button(VC{0.2, 0.2}, VC{WINDOW_WIDTH / 2 - ((6065 / 3) / 2) * 0.2 + 500, WINDOW_HEIGHT / 2 + 50}, sfTrue);
    buttons[2] = create_button(VC{0.2, 0.2}, VC{WINDOW_WIDTH / 2 - ((6065 / 3) / 2) * 0.2 + 500, WINDOW_HEIGHT / 2 + 250}, sfTrue);
    setup_button_texture(&(buttons[0]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[1]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[2]), &square, "img/Blue_button.png");
    setup_button_text(&(buttons[0]), "Start", "font/Xero.ttf", 40);
    setup_button_text(&(buttons[1]), "Options", "font/Xero.ttf", 40);
    setup_button_text(&(buttons[2]), "Quit", "font/Xero.ttf", 40);
    return (buttons);
}

void main_menu(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    button *buttons = create_buttons_menu();
    int open = 1;
    object background = create_object("img/newbg.jpg", VC{0, 0}, VC{1, 1});
    text texte = setup_text("  Planet\nDefender", "font/o_driftbold.ttf", 150);
    sfFloatRect ownscale = sfText_getGlobalBounds(texte.text);

    sfText_setPosition(texte.text, VC{WINDOW_WIDTH / 2 - ownscale.width / 2 + 500, WINDOW_HEIGHT / 2 - 490});
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        get_events(window, keys);
        sfRenderWindow_drawText(window, texte.text, NULL);
        for (int i = 0; i < 3; i++)
            display_button(window, buttons[i], keys);
        update_mouse_cursor(window, mouse);
        if (is_pressed(buttons[0], window, keys) == sfTrue) {
            game(window, mouse, keys, env);
        }
        if (is_pressed(buttons[1], window, keys) == sfTrue) {
            options(window, mouse, keys, env);
            change_button_text(buttons, env);
        }
        if (is_pressed(buttons[2], window, keys) == sfTrue)
            open = 0;
        sfRenderWindow_display(window);
    }
    for (int i = 0; i < 3; i++)
        destroy_button(buttons[i]);
}
