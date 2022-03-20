/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** pause_menu c
*/

#include "csfml.h"
#include "lib.h"
#include "menu.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"

void setup_text_pause(button *buttons, env_t *env)
{
    if (env->langue[0] == 'E') {
        setup_button_text(&(buttons[0]), "Resume", "font/Xero.ttf", 40);
        setup_button_text(&(buttons[1]), "Main menu", "font/Xero.ttf", 40);
        setup_button_text(&(buttons[2]), "Quit", "font/Xero.ttf", 40);
    } else {
        setup_button_text(&(buttons[0]), "Retour", "font/Xero.ttf", 40);
        setup_button_text(&(buttons[1]), "Menu principal", "font/Xero.ttf", 25);
        setup_button_text(&(buttons[2]), "Quitter", "font/Xero.ttf", 40);
    }
}

button *create_buttons_pause(env_t *e)
{
    button *b = malloc(sizeof(button) * 3);
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    b[0] = create_button(VC{0.2, 0.2}, VC{258, 1080 / 2 - 150}, sfTrue);
    b[1] = create_button(VC{0.2, 0.2}, VC{258, 1080 / 2 + 50}, sfTrue);
    b[2] = create_button(VC{0.2, 0.2}, VC{258, 1080 / 2 + 250}, sfTrue);
    for (int i = 0; i < 3; i++) {
        setup_button_texture(&(b[i]), &square, "img/blue_button.png");
        setup_button_sounds(&(b[i]), "sounds/click.ogg", "sounds/hover.ogg", e);
    }
    setup_text_pause(b, e);
    for (int i = 0; i < 3; i++)
        center_button_text(&(b[i]));
    return (b);
}

void free_pause_menu(object backfr, object backen, text texte, button *buttons)
{
    sfText_destroy(texte.text);
    sfFont_destroy(texte.font);
    sfSprite_destroy(backen.sprite);
    sfSprite_destroy(backfr.sprite);
    sfTexture_destroy(backen.texture);
    sfTexture_destroy(backfr.texture);
    for (int i = 0; i < 3; i++)
        destroy_button(buttons[i]);
}

int pause_menu_events(sfRenderWindow *window, env_t *env, button *bu, int *ret)
{
    sfRenderWindow_clear(window, sfBlack);
    get_events(window, env->keys);
    if (is_pressed(bu[0], window, env->keys) || env->keys[sfKeyEscape] == 3)
        return 0;
    if (is_pressed(bu[1], window, env->keys)) {
        *ret = 1;
        return 0;
    }
    if (is_pressed(bu[2], window, env->keys))
        sfRenderWindow_close(window);
    return 1;
}

int pause_menu(sfRenderWindow *window, object mouse, env_t *env)
{
    int open = 1;
    int to_return = 0;
    button *bu = create_buttons_pause(env);
    text texte = setup_text("   Pause", "font/o_driftbold.ttf", 150);
    object backfr = create_object("img/pause_fr.jpg", VC{0, 0}, VC{1, 1});
    object backen = create_object("img/pause_en.jpg", VC{0, 0}, VC{1, 1});

    sfText_setPosition(texte.text, VC{135, 120});
    while (sfRenderWindow_isOpen(window) && open) {
        open = pause_menu_events(window, env, bu, &to_return);
        display_background(window, backfr, backen, env);
        for (int i = 0; i < 3; i++)
            display_button(window, &(bu[i]), env->keys);
        sfRenderWindow_drawText(window, texte.text, NULL);
        update_mouse_cursor(window, mouse, env->tempo);
        sfRenderWindow_display(window);
    }
    free_pause_menu(backfr, backen, texte, bu);
    env->keys[sfKeyEscape] = 0;
    return (to_return);
}
