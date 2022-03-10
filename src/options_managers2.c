/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** options_managers2
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "menu.h"
#include "events.h"

void resolution_calculator(int *resolution)
{
    switch ((*resolution)) {
    case 1920:
        (*resolution) = 1680;
        break;
    case 1680:
        (*resolution) = 1440;
        break;
    case 1440:
        (*resolution) = 1360;
        break;
    case 1360:
        (*resolution) = 1280;
        break;
    case 1280:
        (*resolution) = 1072;
        break;
    case 1072:
        (*resolution) = 1920;
        break;
    }
}

void langue_manager(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    if (is_pressed(but[9], window, keys) && env->langue[0] != 'E') {
        env->langue = my_strdup("EN");
        setup_buttons_options(but, env);
    }
    if (is_pressed(but[8], window, keys) && env->langue[0] != 'F') {
        env->langue = my_strdup("FR");
        setup_buttons_options(but, env);
    }
}

void resolution_manager(button *but, sfRenderWindow *window, int *k, env_t *env)
{
    int res;

    if (is_pressed(but[6], window, k)) {
        resolution_calculator(&env->resolution);
        res = env->resolution / 16 * 9;
        sfRenderWindow_setSize(window, (sfVector2u){env->resolution, res});
        set_button_resolution_txt(&(but[6]), env);
    }
}

void screen_manager(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    if (is_pressed(but[2], window, keys) != sfTrue)
        return;
    if (env->screen_type == 0) {
        env->screen_type = 1;
        sfRenderWindow_destroy(window);
        window = create_windows(env);
    } else if (env->screen_type == 1) {
        env->screen_type = 2;
        env->resolution = 1920;
        set_button_resolution_txt(&(but[6]), env);
        sfRenderWindow_destroy(window);
        window = create_windows(env);
    } else if (env->screen_type == 2) {
        env->screen_type = 0;
        sfRenderWindow_destroy(window);
        window = create_windows(env);
    }
    set_button_screen_txt(&(but[2]), env);
}

void vsync_manager(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    if (is_pressed(but[7], window, keys)) {
        env->vsync = (env->vsync == 0);
        if (env->vsync == 0)
            sfRenderWindow_setVerticalSyncEnabled(window, sfFalse);
        else
            sfRenderWindow_setVerticalSyncEnabled(window, sfTrue);
        set_button_vsync_txt(&(but[7]), env);
    }
}
