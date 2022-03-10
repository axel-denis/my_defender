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
#include "menu.h"
#include "button.h"
#include "events.h"

void set_text_options(button *buttons, env_t *env)
{
    setup_button_text(&(buttons[2]), NULL, "font/Xero.ttf", 22);
    setup_button_text(&(buttons[3]), NULL, "font/Xero.ttf", 40);
    setup_button_text(&(buttons[4]), NULL, "font/Xero.ttf", 30);
    setup_button_text(&(buttons[5]), NULL, "font/Xero.ttf", 30);
    setup_button_text(&(buttons[6]), NULL, "font/Xero.ttf", 25);
    setup_button_text(&(buttons[7]), NULL, "font/Xero.ttf", 30);
    setup_buttons_options(buttons, env);
}

void set_textures_options(button *buttons)
{
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);
    sfIntRect square2 = create_rect(0, 0, 1920 / 3, 640);

    setup_button_texture(&(buttons[0]), &square, "img/arrow.png");
    setup_button_texture(&(buttons[1]), &square, "img/arrow.png");
    setup_button_texture(&(buttons[2]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[3]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[4]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[5]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[6]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[7]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[8]), &square2, "img/france.png");
    setup_button_texture(&(buttons[9]), &square2, "img/anglois.png");
}

button *create_buttons_options(env_t *env)
{
    button *buttons = malloc(sizeof(button) * 10);

    buttons[0] = create_button(VC{.4, .4}, VC{440 + 200, 400 + 261}, sfFalse);
    buttons[1] = create_button(VC{-.4, .4}, VC{440 - 200, 400 + 261}, sfFalse);
    buttons[2] = create_button(VC{0.2, 0.2}, VC{238 - 220, 400 - 150}, sfTrue);
    buttons[3] = create_button(VC{0.2, 0.2}, VC{238, 400 + 450}, sfTrue);
    buttons[5] = create_button(VC{0.2, 0.2}, VC{238 - 220, 400 + 50}, sfTrue);
    buttons[4] = create_button(VC{0.2, 0.2}, VC{238, 400 + 250}, sfTrue);
    buttons[6] = create_button(VC{0.2, 0.2}, VC{238 + 220, 400 + 50}, sfTrue);
    buttons[7] = create_button(VC{0.2, 0.2}, VC{238 + 220, 400 - 150}, sfTrue);
    buttons[8] = create_button(VC{0.1, 0.1}, VC{1840, 20}, sfFalse);
    buttons[9] = create_button(VC{0.1, 0.1}, VC{1750, 20}, sfFalse);
    set_textures_options(buttons);
    set_text_options(buttons, env);
    for (int i = 0; i < 10 ; i++)
        setup_button_sounds(&(buttons[i]), "sounds/click.ogg", "sounds/hover.ogg", env);
    return (buttons);
}

void setup_buttons_options(button *buttons, env_t *env)
{
    if (env->langue[0] == 'E')
        sfText_setString(buttons[3].text.text, "Resume");
    else
        sfText_setString(buttons[3].text.text, "Retour");
    center_button_text(&(buttons[3]));
    set_button_volume_txt(&(buttons[4]), env);
    set_button_fps_txt(&(buttons[5]), env);
    set_button_resolution_txt(&(buttons[6]), env);
    set_button_vsync_txt(&(buttons[7]), env);
    set_button_screen_txt(&(buttons[2]), env);
}
