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

    object background;

    background.texture = sfTexture_createFromFile("img/space.jpg", NULL);
    background.sprite = sfSprite_create();
    sfSprite_setTexture(background.sprite, background.texture, sfFalse);
    sfSprite_setScale(background.sprite, VC{0.55, 0.55});
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        sfSprite_setScale(get_case_from_mouse(env, get_true_mouse_pos(window)), (sfVector2f) {.5, .5});
        display_map(env, window);
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

int main(int ac, char **av)
{
    int *keys = init_keys();
    sfVideoMode main_w = {1920, 1080, 64};
    sfRenderWindow *window;
    object mouse = setup_mouse("img/cursor.png", VC{0.05, 0.05});
    env_t *env = create_env();

    window = sfRenderWindow_create(main_w, "My defender", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    if (read_map(env, "map") == 1) {
        my_errorstr("Error on map\n");
        return 84;
    }
    main_menu(window, mouse, keys, env);
    destroy_object(mouse);
    return (0);
}
