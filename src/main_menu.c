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
        sfText_setString(buttons[2].text.text, "How to play");
        sfText_setString(buttons[3].text.text, "Quit");
    } else {
        sfText_setString(buttons[0].text.text, "Demarrer");
        sfText_setString(buttons[1].text.text, "Options");
        sfText_setString(buttons[2].text.text, "Tutoriel");
        sfText_setString(buttons[3].text.text, "Quitter");
    }
    for (int i = 0; i < 4; i++)
        center_button_text(&(buttons[i]));
}

button *create_buttons_menu(env_t *e)
{
    button *b = malloc(sizeof(button) * 4);
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    b[0] = create_button(VC{.2, .2}, VC{1258, 320}, sfTrue);
    b[1] = create_button(VC{.2, .2}, VC{1258, 500}, sfTrue);
    b[2] = create_button(VC{.2, .2}, VC{1258, 680}, sfTrue);
    b[3] = create_button(VC{.2, .2}, VC{1258, 860}, sfTrue);
    for (int i = 0; i < 4; i++) {
        setup_button_texture(&(b[i]), &square, "img/Blue_button.png");
        setup_button_sounds(&(b[i]), "sounds/click.ogg", "sounds/hover.ogg", e);
    }
    setup_button_text(&(b[0]), "Start", "font/Xero.ttf", 40);
    setup_button_text(&(b[1]), "Options", "font/Xero.ttf", 40);
    setup_button_text(&(b[2]), "How to play", "font/Xero.ttf", 30);
    setup_button_text(&(b[3]), "Quit", "font/Xero.ttf", 40);
    return (b);
}

int main_menu_button_gestion(SFWIN win, button *but, object mouse, env_t *env)
{
    for (int i = 0; i < 4; i++)
        display_button(win, &(but[i]), env->keys);
    update_mouse_cursor(win, mouse, env->tempo);
    if (is_pressed(but[0], win, env->keys) == sfTrue) {
        game(win, mouse, env);
    }
    if (is_pressed(but[1], win, env->keys) == sfTrue) {
        options(win, mouse, env->keys, env);
        change_button_text(but, env);
        for (int i = 0; i < 4; i++) {
            sfSound_setVolume(but[i].click, env->volume);
            sfSound_setVolume(but[i].hover, env->volume / 1.4);
        }
    }
    if (is_pressed(but[3], win, env->keys) == sfTrue)
        return 0;
    if (is_pressed(but[2], win, env->keys) == sfTrue)
        how_to_menu(win, mouse, env);
    return 1;
}

void main_menu(sfRenderWindow *window, object mouse, env_t *env)
{
    button *buttons = create_buttons_menu(env);
    int open = 1;
    object background = create_object("img/newbg.jpg", VC{0, 0}, VC{1, 1});
    text texte = setup_text("  Planet\nDefender", "font/o_driftbold.ttf", 150);

    sfText_setPosition(texte.text, VC{1131, 0});
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        get_events(window, env->keys);
        sfRenderWindow_drawText(window, texte.text, NULL);
        open = main_menu_button_gestion(window, buttons, mouse, env);
        sfRenderWindow_display(window);
    }
    sfSprite_destroy(background.sprite);
    sfTexture_destroy(background.texture);
    sfText_destroy(texte.text);
    sfFont_destroy(texte.font);
    for (int i = 0; i < 4; i++)
        destroy_button(buttons[i]);
}
