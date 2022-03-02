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

void options(sfRenderWindow *window, object mouse, int *keys)
{
    int open = 1;

    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
    }
    keys[sfKeyEscape] = 0;
}

void game(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    object background = create_object("img/space.jpg", VC{0, 0}, VC{.55, .55});
    object planet = create_object("img/planet.png", VC{2300, 980}, VC{.4, .4});
    object planet2 = create_object("img/planet2.png", VC{300, 700}, VC{.3, .3});
    object milkeyway = create_object("img/milkey_way.png", VC{0, 0}, VC{1, 1});
    object epsilon = create_object("img/Epsilon.png", VC{0, 0}, VC{.1, .1});
    object stats = create_object("img/wide_blue_display.png", VC{0, 0}, VC{.7, .3});

    sfSprite_setColor(planet2.sprite, sfColor_fromRGB(175, 175, 175));
    sfSprite_setColor(planet.sprite, sfColor_fromRGB(150, 150, 150));
    sfSprite_setRotation(planet.sprite, 180);
    sfSprite_setRotation(planet2.sprite, -100);
    setmap_opacity(env);
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        sfRenderWindow_drawSprite(window, milkeyway.sprite, NULL);
        sfRenderWindow_drawSprite(window, planet.sprite, NULL);
        sfRenderWindow_drawSprite(window, planet2.sprite, NULL);
        sfRenderWindow_drawSprite(window, epsilon.sprite, NULL);
        display_map(env, window);
        sfRenderWindow_drawSprite(window, stats.sprite, NULL);
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
    env->score = 0;
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
