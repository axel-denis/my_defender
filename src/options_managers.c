/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** options
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"

void langue_manager(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    int mod = 0;
    char *language_txt;

    if (is_pressed(but[2], window, keys) && env->langue[0] == 'E') {
        env->langue = my_strdup("FR");
        language_txt = my_strdup("Langue: ");
        my_strcat(language_txt, env->langue);
        sfText_setString(but[2].text.text, language_txt);
        sfText_setString(but[3].text.text, "Retour");
        mod = 1;
    }
    if (is_pressed(but[2], window, keys) && env->langue[0] == 'F' && mod == 0) {
        env->langue = my_strdup("EN");
        language_txt = my_strdup("Language: ");
        my_strcat(language_txt, env->langue);
        sfText_setString(but[2].text.text, language_txt);
        sfText_setString(but[3].text.text, "Return");
    }
    center_button_text(&(but[2]));
    center_button_text(&(but[3]));
}

void fps_manager(button *but, sfRenderWindow *window, int *keys, env_t *env)
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
}

void volume_manager(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    char *volume_txt;

    if (is_pressed(but[0], window, keys) == sfTrue && env->volume < 100) {
        env->volume += 1;
        volume_txt = my_strdup("Volume: ");
        my_strcat(volume_txt, my_nbr_to_str(env->volume));
        sfText_setString(but[4].text.text, volume_txt);
    }
    if (is_pressed(but[1], window, keys) == sfTrue && env->volume > 0) {
        env->volume -= 1;
        volume_txt = my_strdup("Volume: ");
        my_strcat(volume_txt, my_nbr_to_str(env->volume));
        sfText_setString(but[4].text.text, volume_txt);
    }
}

void volume_manager2(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    int changed = 0;
    char *volume_txt;

    if (is_pressed(but[4], window, keys) && env->volume == 0) {
        env->volume = 100;
        volume_txt = my_strdup("Volume: ");
        my_strcat(volume_txt, my_nbr_to_str(env->volume));
        sfText_setString(but[4].text.text, volume_txt);
        changed = 1;
    }
    if (is_pressed(but[4], window, keys) && env->volume != 0 && changed == 0) {
        env->volume = 0;
        volume_txt = my_strdup("Volume: ");
        my_strcat(volume_txt, my_nbr_to_str(env->volume));
        sfText_setString(but[4].text.text, volume_txt);
    }
    for (int i = 0; i < 5; i++) {
        sfSound_setVolume(but[i].click, env->volume);
        sfSound_setVolume(but[i].hover, env->volume);
    }
}
