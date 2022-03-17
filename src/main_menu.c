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
    for (int i = 0; i < 3; i++)
        center_button_text(&(buttons[i]));
}

button *create_buttons_menu(env_t *e)
{
    button *b = malloc(sizeof(button) * 3);
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    b[0] = create_button(VC{.2, .2}, VC{1258, 390}, sfTrue);
    b[1] = create_button(VC{.2, .2}, VC{1258, 590}, sfTrue);
    b[2] = create_button(VC{.2, .2}, VC{1258, 790}, sfTrue);
    for (int i = 0; i < 3; i++) {
        setup_button_texture(&(b[i]), &square, "img/Blue_button.png");
        setup_button_sounds(&(b[i]), "sounds/click.ogg", "sounds/hover.ogg", e);
    }
    setup_button_text(&(b[0]), "Start", "font/Xero.ttf", 40);
    setup_button_text(&(b[1]), "Options", "font/Xero.ttf", 40);
    setup_button_text(&(b[2]), "Quit", "font/Xero.ttf", 40);
    return (b);
}

void main_menu(sfRenderWindow *window, object mouse, env_t *env)
{
    button *buttons = create_buttons_menu(env);
    int open = 1;
    object background = create_object("img/newbg.jpg", VC{0, 0}, VC{1, 1});
    text texte = setup_text("  Planet\nDefender", "font/o_driftbold.ttf", 150);

    sfText_setPosition(texte.text, VC{1131, 50});
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        get_events(window, env->keys);
        sfRenderWindow_drawText(window, texte.text, NULL);
        for (int i = 0; i < 3; i++)
            display_button(window, &(buttons[i]), env->keys);
        update_mouse_cursor(window, mouse, env->tempo);
        if (is_pressed(buttons[0], window, env->keys) == sfTrue) {
            game(window, mouse, env);
        }
        if (is_pressed(buttons[1], window, env->keys) == sfTrue) {
            options(window, mouse, env->keys, env);
            change_button_text(buttons, env);
            for (int i = 0; i < 3; i++) {
                sfSound_setVolume(buttons[i].click, env->volume);
                sfSound_setVolume(buttons[i].hover, env->volume/1.4);
            }
        }
        if (is_pressed(buttons[2], window, env->keys) == sfTrue)
            open = 0;
        sfRenderWindow_display(window);
    }
    sfSprite_destroy(background.sprite);
    sfTexture_destroy(background.texture);
    sfText_destroy(texte.text);
    sfFont_destroy(texte.font);
    for (int i = 0; i < 3; i++)
        destroy_button(buttons[i]);
}
