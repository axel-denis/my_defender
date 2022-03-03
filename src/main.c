/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** main.c
*/

#include "menu.h"
#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"
#include "map.h"

button *create_buttons_options(void)
{
    button *buttons = malloc(sizeof(button) * 2);
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    buttons[0] = create_button(VC{0.2, 0.2}, VC{WINDOW_WIDTH / 2 -
        ((6065 / 3) / 2) * 0.2 + 500, WINDOW_HEIGHT / 2 - 150}, sfTrue);
    buttons[1] = create_button(VC{0.2, 0.2}, VC{WINDOW_WIDTH / 2 -
        ((6065 / 3) / 2) * 0.2 + 500, WINDOW_HEIGHT / 2 + 50}, sfTrue);
    setup_button_texture(&(buttons[0]), &square, "img/arrow.png");
    setup_button_texture(&(buttons[1]), &square, "img/arrow.png");
    setup_button_text(&(buttons[0]), "Start", "font/Absolute-Xero.ttf", 40);
    setup_button_text(&(buttons[1]), "Options", "font/Absolute-Xero.ttf", 40);
    return (buttons);
}

void options(sfRenderWindow *window, object mouse, int *keys)
{
    int open = 1;
    button *buttons = create_buttons_options();

    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        for (int i = 0; i < 2; i++)
            display_button(window, buttons[i], keys);
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
    }
    keys[sfKeyEscape] = 0;
}

void game(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    float money = 10000;
    float electricity = 0;
    float steel = 0;
    object background = create_object("img/background.jpg", VC{0, 0}, VC{1, 1});

    object epsilon = create_object("img/Epsilon.png", VC{1370, 35}, VC{.1, .1});
    object stats = create_object("img/wide_blue_display.png", VC{1285, 5}, VC{.6, .3});
    object cadre = create_object("img/temp.png", VC{0, 836 - 20}, VC{1, 0.6});
    text money_text = setup_text(my_nbr_to_str(money) , "font/oceanicdrift.ttf", 45);

    object button1 = create_object("img/Blue_button.png", VC{50, 836 - 20}, VC{0.3, 0.3});
    object button2 = create_object("img/Blue_button.png", VC{50, 836 - 20}, VC{0.3, 0.3});

    sfText_setPosition(money_text.text, VC{1430, 24});
    setmap_opacity(env);
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        display_map(env, window);
        sfRenderWindow_drawSprite(window, stats.sprite, NULL);
        sfRenderWindow_drawSprite(window, epsilon.sprite, NULL);
        sfRenderWindow_drawText(window, money_text.text, NULL);
        sfRenderWindow_drawSprite(window, button1.sprite, NULL);
        sfRenderWindow_drawSprite(window, button2.sprite, NULL);
        sfRenderWindow_drawSprite(window, cadre.sprite, NULL);
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
    }
    keys[sfKeyEscape] = 0;
}

env_t *create_env(void)
{
    env_t *env = malloc(sizeof(env_t));

    env->data.ground_texture =
        sfTexture_createFromFile("img/grass.png", NULL);
    env->data.path_texture = sfTexture_createFromFile("img/dirt.png", NULL);
    env->player_stats.score = 0;
    return env;
}

int main(void)
{
    int *keys = init_keys();
    sfVideoMode main_w = {1920, 1080, 64};
    sfRenderWindow *window;
    object mouse = setup_mouse("img/cursor.png", VC{0.05, 0.05});
    env_t *env = create_env();

    window = sfRenderWindow_create(main_w, "My defender", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 75);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    if (read_map(env, "map") == 1) {
        my_errorstr("Error on map\n");
        return 84;
    }
    main_menu(window, mouse, keys, env);
    destroy_object(mouse);
    return (0);
}
