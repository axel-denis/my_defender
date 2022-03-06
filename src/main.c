/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** main.c
*/

#include "menu.h"
#include "enemy.h"
#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"
#include "map.h"

button *create_buttons_options(void)
{
    button *buttons = malloc(sizeof(button) * 5);
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    buttons[0] = create_button(VC{.4, .4}, VC{WINDOW_WIDTH / 2 + 200 - 500, WINDOW_HEIGHT / 2 + 61}, sfFalse);
    buttons[1] = create_button(VC{-.4, .4}, VC{WINDOW_WIDTH / 2 - 200 - 500, WINDOW_HEIGHT / 2 + 61}, sfFalse);
    buttons[2] = create_button(VC{0.2, 0.2}, VC{WINDOW_WIDTH / 2 - (((6065 / 3) / 2) * 0.2) - 500, WINDOW_HEIGHT / 2 - 150}, sfTrue);
    buttons[3] = create_button(VC{0.2, 0.2}, VC{WINDOW_WIDTH / 2 - (((6065 / 3) / 2) * 0.2) - 500, WINDOW_HEIGHT / 2 + 250}, sfTrue);
    buttons[4] = create_button(VC{0.2, 0.2}, VC{WINDOW_WIDTH / 2 - (((6065 / 3) / 2) * 0.2) - 500, WINDOW_HEIGHT / 2 + 50}, sfTrue);
    setup_button_texture(&(buttons[0]), &square, "img/arrow.png");
    setup_button_texture(&(buttons[1]), &square, "img/arrow.png");
    setup_button_texture(&(buttons[2]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[3]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[4]), &square, "img/Blue_button.png");
    setup_button_text(&(buttons[2]), "Language: ", "font/Absolute-Xero.ttf", 30);
    setup_button_text(&(buttons[3]), "Return", "font/Absolute-Xero.ttf", 40);
    setup_button_text(&(buttons[4]), "Volume: ", "font/Absolute-Xero.ttf", 30);
    return (buttons);
}

void options(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    int changed = 0;
    button *buttons = create_buttons_options();
    char *volume_txt = my_strdup("Volume: ");
    char *language_txt = my_strdup("Language: ");
    text texte = setup_text("  Options", "font/oceanicdriftbold.ttf", 150);
    object background = create_object("img/bg.jpg", VC{0, 0}, VC{1, 1});

    sfText_setPosition(texte.text, VC{WINDOW_WIDTH / 2 - 860, WINDOW_HEIGHT / 2 - 360 - 50});
    my_strcat(language_txt, env->langue);
    my_strcat(volume_txt, my_nbr_to_str(env->volume));
    sfText_setString(buttons[4].text.text, volume_txt);
    sfText_setString(buttons[2].text.text, language_txt);
    center_button_text(&(buttons[4]));
    center_button_text(&(buttons[2]));
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        if (is_pressed(buttons[0], window, keys) == sfTrue && env->volume < 100) {
            env->volume += 1;
            volume_txt = my_strdup("Volume: ");
            my_strcat(volume_txt, my_nbr_to_str(env->volume));
            sfText_setString(buttons[4].text.text, volume_txt);
        }
        if (is_pressed(buttons[2], window, keys) && env->langue[0] == 'E') {
            env->langue = my_strdup("FR");
            language_txt = my_strdup("Language: ");
            my_strcat(language_txt, env->langue);
            sfText_setString(buttons[2].text.text, language_txt);
            changed = 1;
        }
        if (is_pressed(buttons[2], window, keys) && env->langue[0] == 'F' && changed == 0) {
            env->langue = my_strdup("EN");
            language_txt = my_strdup("Language: ");
            my_strcat(language_txt, env->langue);
            sfText_setString(buttons[2].text.text, language_txt);
        }
        if (is_pressed(buttons[1], window, keys) == sfTrue && env->volume > 0) {
            env->volume -= 1;
            volume_txt = my_strdup("Volume: ");
            my_strcat(volume_txt, my_nbr_to_str(env->volume));
            sfText_setString(buttons[4].text.text, volume_txt);
        }
        if (is_pressed(buttons[4], window, keys) && env->volume == 0) {
            env->volume = 100;
            volume_txt = my_strdup("Volume: ");
            my_strcat(volume_txt, my_nbr_to_str(env->volume));
            sfText_setString(buttons[4].text.text, volume_txt);
            changed = 1;
        }
        if (is_pressed(buttons[4], window, keys) && env->volume != 0 && changed == 0) {
            env->volume = 0;
            volume_txt = my_strdup("Volume: ");
            my_strcat(volume_txt, my_nbr_to_str(env->volume));
            sfText_setString(buttons[4].text.text, volume_txt);
        }
        if (is_pressed(buttons[3], window, keys))
            open = 0;
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        sfRenderWindow_drawText(window, texte.text, NULL);
        for (int i = 0; i < 5; i++)
            display_button(window, buttons[i], keys);
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
        changed = 0;
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
    object worm_hole = create_object("img/icon.png", VC{env->starting_square.x * 60 , env->starting_square.y * 60 - 58}, VC{.3, 1});
    object epsilon = create_object("img/Epsilon.png", VC{1370, 35}, VC{.1, .1});
    object stats = create_object("img/blue_display.png", VC{1285, 5}, VC{1, 1});
    object cadre = create_object("img/temp.png", VC{0, 836 - 20}, VC{1, 0.6});
    enemy mob = create_enemy_type_1(env);
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
        sfRenderWindow_drawSprite(window, worm_hole.sprite, NULL);
        sfRenderWindow_drawSprite(window, mob.sprite, NULL);
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
        evolve_enemy(env, &mob);
    }
    keys[sfKeyEscape] = 0;
}

env_t *create_env(void)
{
    env_t *env = malloc(sizeof(env_t));

    env->volume = 100;
    env->langue = my_strdup("EN");
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
