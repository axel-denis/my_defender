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

button *create_buttons_options(void)
{
    button *buttons = malloc(sizeof(button) * 5);
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    buttons[0] = create_button(VC{.4, .4}, VC{460 + 200, 540 + 61}, sfFalse);
    buttons[1] = create_button(VC{-.4, .4}, VC{460 - 200, 540 + 61}, sfFalse);
    buttons[2] = create_button(VC{0.2, 0.2}, VC{258, 540 - 150}, sfTrue);
    buttons[3] = create_button(VC{0.2, 0.2}, VC{258, 540 + 250}, sfTrue);
    buttons[4] = create_button(VC{0.2, 0.2}, VC{258, 540 + 50}, sfTrue);
    setup_button_texture(&(buttons[0]), &square, "img/arrow.png");
    setup_button_texture(&(buttons[1]), &square, "img/arrow.png");
    setup_button_texture(&(buttons[2]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[3]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[4]), &square, "img/Blue_button.png");
    setup_button_text(&(buttons[2]), "Language: ", "font/Xero.ttf", 30);
    setup_button_text(&(buttons[3]), "Return", "font/Xero.ttf", 40);
    setup_button_text(&(buttons[4]), "Volume: ", "font/Xero.ttf", 30);
    return (buttons);
}

button *setup_buttons_options(button *buttons, env_t *env)
{
    char *volume_txt = my_strdup("Volume: ");
    char *language_txt = my_strdup("Language: ");

    my_strcat(language_txt, env->langue);
    my_strcat(volume_txt, my_nbr_to_str(env->volume));
    sfText_setString(buttons[4].text.text, volume_txt);
    sfText_setString(buttons[2].text.text, language_txt);
    center_button_text(&(buttons[4]));
    center_button_text(&(buttons[2]));
}

void langue_manager(button *but, sfRenderWindow *window, int *keys, env_t *env)
{
    int mod = 0;
    char *language_txt;

    if (is_pressed(but[2], window, keys) && env->langue[0] == 'E') {
            env->langue = my_strdup("FR");
            language_txt = my_strdup("Language: ");
            my_strcat(language_txt, env->langue);
            sfText_setString(but[2].text.text, language_txt);
            mod = 1;
    }
    if (is_pressed(but[2], window, keys) && env->langue[0] == 'F' && mod == 0) {
        env->langue = my_strdup("EN");
        language_txt = my_strdup("Language: ");
        my_strcat(language_txt, env->langue);
        sfText_setString(but[2].text.text, language_txt);
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
}
