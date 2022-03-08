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

void set_textures_options(button *buttons)
{
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    setup_button_texture(&(buttons[0]), &square, "img/arrow.png");
    setup_button_texture(&(buttons[1]), &square, "img/arrow.png");
    setup_button_texture(&(buttons[2]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[3]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[4]), &square, "img/Blue_button.png");
}

button *create_buttons_options(env_t *env)
{
    button *buttons = malloc(sizeof(button) * 5);

    buttons[0] = create_button(VC{.4, .4}, VC{460 + 200, 540 + 61}, sfFalse);
    buttons[1] = create_button(VC{-.4, .4}, VC{460 - 200, 540 + 61}, sfFalse);
    buttons[2] = create_button(VC{0.2, 0.2}, VC{258, 540 - 150}, sfTrue);
    buttons[3] = create_button(VC{0.2, 0.2}, VC{258, 540 + 250}, sfTrue);
    buttons[4] = create_button(VC{0.2, 0.2}, VC{258, 540 + 50}, sfTrue);
    set_textures_options(buttons);
    if (env->langue[0] == 'F') {
        setup_button_text(&(buttons[2]), "Langue: ", "font/Xero.ttf", 30);
        setup_button_text(&(buttons[3]), "Retour", "font/Xero.ttf", 40);
    } else {
        setup_button_text(&(buttons[2]), "Language: ", "font/Xero.ttf", 30);
        setup_button_text(&(buttons[3]), "Return", "font/Xero.ttf", 40);
    }
    setup_button_text(&(buttons[4]), "Volume: ", "font/Xero.ttf", 30);
    for (int i = 0; i < 5; i++)
        setup_button_sounds(&(buttons[i]), "sounds/click.ogg", "sounds/hover.ogg", env);
    return (buttons);
}

void setup_buttons_options(button *buttons, env_t *env)
{
    char *volume_txt = my_strdup("Volume: ");
    char *language_txt = my_strdup("Language: ");

    my_strcat(language_txt, env->langue);
    my_strcat(volume_txt, my_dec_to_base(env->volume, "0123456789"));
    sfText_setString(buttons[4].text.text, volume_txt);
    sfText_setString(buttons[2].text.text, language_txt);
    center_button_text(&(buttons[4]));
    center_button_text(&(buttons[2]));
}

/*     char *volume_txt = strdup("Volume: ");
    char *language_txt = strdup("Language: ");

    language_txt = strcat(language_txt, env->langue);
    volume_txt = strcat(volume_txt, my_dec_to_base(env->volume, "0123456789"));
    sfText_setString(buttons[4].text.text, volume_txt);
    sfText_setString(buttons[2].text.text, language_txt);
    center_button_text(&(buttons[4]));
    center_button_text(&(buttons[2])); */
