/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** options c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "menu.h"
#include "events.h"

void fps_manager2(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    if (is_pressed(but[5], window, keys) == sfTrue && env->fps == 75) {
        env->fps = 144;
        sfRenderWindow_setFramerateLimit(window, env->fps);
        sfText_setString(but[5].text.text, "fps: 144");
        return;
    }
    if (is_pressed(but[5], window, keys) == sfTrue && env->fps == 144) {
        env->fps = 240;
        sfRenderWindow_setFramerateLimit(window, env->fps);
        sfText_setString(but[5].text.text, "fps: 240");
        return;
    }
}

void fps_manager(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    if (is_pressed(but[5], window, keys) == sfTrue && env->fps == 240) {
        env->fps = 30;
        sfRenderWindow_setFramerateLimit(window, env->fps);
        sfText_setString(but[5].text.text, "fps: 30");
        return;
    }
    if (is_pressed(but[5], window, keys) == sfTrue && env->fps == 30) {
        env->fps = 60;
        sfRenderWindow_setFramerateLimit(window, env->fps);
        sfText_setString(but[5].text.text, "fps: 60");
        return;
    }
    if (is_pressed(but[5], window, keys) == sfTrue && env->fps == 60) {
        env->fps = 75;
        sfRenderWindow_setFramerateLimit(window, env->fps);
        sfText_setString(but[5].text.text, "fps: 75");
        return;
    }
    fps_manager2(but, window, keys, env);
}

void volume_manager(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    if (is_pressed(but[0], window, keys) == sfTrue && env->volume < 100) {
        env->volume += 1;
        set_button_volume_txt(&(but[4]), env);
    }
    if (is_pressed(but[1], window, keys) == sfTrue && env->volume > 0) {
        env->volume -= 1;
        set_button_volume_txt(&(but[4]), env);
    }
}

void volume_manager2(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    if (is_pressed(but[4], window, keys) == sfTrue) {
        if (env->volume == 0)
            env->volume = 100;
        else
            env->volume = 0;
        set_button_volume_txt(&(but[4]), env);
    }
    for (int i = 0; i < 10; i++) {
        sfSound_setVolume(but[i].click, env->volume);
        sfSound_setVolume(but[i].hover, env->volume / 1.4);
    }
}

char *set_screen_txt(env_t *env)
{
    char *screen;

    if (env->screen_type == 0)
        screen = my_strdup("normal");
    if (env->screen_type == 1 && ENGLISH)
        screen = my_strdup("borderless");
    if (env->screen_type == 1 && !ENGLISH)
        screen = my_strdup("sans bords");
    if (env->screen_type == 2 && ENGLISH)
        screen = my_strdup("fullscreen");
    if (env->screen_type == 2 && !ENGLISH)
        screen = my_strdup("plein ecran");
    return (screen);
}
