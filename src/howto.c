/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** howto menu
*/

#include "csfml.h"
#include "lib.h"
#include "menu.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"

button create_buttons_how_to(env_t *env)
{
    button but;
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    but = create_button(VC{0.2, 0.2}, VC{1920 - 410, 1080 - 170}, sfTrue);
    setup_button_texture(&but, &square, "img/blue_button.png");
    setup_button_sounds(&but, "sounds/click.ogg", "sounds/hover.ogg", env);
    if (env->langue[0] == 'E')
        setup_button_text(&but, "Resume", "font/Xero.ttf", 40);
    else
        setup_button_text(&but, "Retour", "font/Xero.ttf", 40);
    center_button_text(&but);
    return (but);
}

void free_how_to_menu(object backfr, object backen, button button)
{
    sfSprite_destroy(backen.sprite);
    sfSprite_destroy(backfr.sprite);
    sfTexture_destroy(backen.texture);
    sfTexture_destroy(backfr.texture);
    destroy_button(button);
}

int how_to_menu_events(sfRenderWindow *window, env_t *env, button bu)
{
    sfRenderWindow_clear(window, sfBlack);
    get_events(window, env->keys);
    if (is_pressed(bu, window, env->keys) || env->keys[sfKeyEscape] == 3)
        return 0;
    return 1;
}

void how_to_menu(sfRenderWindow *window, object mouse, env_t *env)
{
    int open = 1;
    button button = create_buttons_how_to(env);
    object backfr = create_object("img/howto_fr.jpg", VC{0, 0}, VC{1, 1});
    object backen = create_object("img/howto_en.jpg", VC{0, 0}, VC{1, 1});

    while (sfRenderWindow_isOpen(window) && open) {
        open = how_to_menu_events(window, env, button);
        display_background(window, backfr, backen, env);
        display_button(window, &button, env->keys);
        update_mouse_cursor(window, mouse, env->tempo);
        sfRenderWindow_display(window);
    }
    free_how_to_menu(backfr, backen, button);
    env->keys[sfKeyEscape] = 0;
}
