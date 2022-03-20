/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** pause_menu
*/

#include "csfml.h"
#include "lib.h"
#include "menu.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"

void setup_buttons(env_t *env, button *buttons)
{
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    for (int i = 0; i < 2; i++) {
        setup_button_texture(&(buttons[i]), &square, "img/Blue_button.png");
        setup_button_sounds(&(buttons[i]),
            "sounds/click.ogg", "sounds/hover.ogg", env);
    }
    if (env->langue[0] == 'E') {
        setup_button_text(&(buttons[0]), "Main menu", "font/Xero.ttf", 40);
        setup_button_text(&(buttons[1]), "Quit", "font/Xero.ttf", 40);
    } else {
        setup_button_text(&(buttons[0]), "Menu principal", "font/Xero.ttf", 25);
        setup_button_text(&(buttons[1]), "Quitter", "font/Xero.ttf", 40);
    }
    for (int i = 0; i < 2; i++)
        center_button_text(&(buttons[i]));
}

button *create_buttons_lose(env_t *env)
{
    button *buttons = malloc(sizeof(button) * 2);

    buttons[0] = create_button(VC{0.2, 0.2}, VC{758, 540}, sfTrue);
    buttons[1] = create_button(VC{0.2, 0.2}, VC{758, 740}, sfTrue);
    setup_buttons(env, buttons);
    return (buttons);
}

int render_loose_menu(SFWIN window, int *keys, button *buttons, env_t *env)
{
    int open = 1;
    object backfr = create_object("img/lose.jpg", VC{0, 0}, VC{1, 1});

    sfRenderWindow_clear(window, sfBlack);
    get_events(window, keys);
    if (keys[sfKeyEscape] == 3)
        open = 0;
    if (is_pressed(buttons[0], window, keys))
        open = 0;
    if (is_pressed(buttons[1], window, keys))
        sfRenderWindow_close(window);
    sfRenderWindow_drawSprite(window, backfr.sprite, NULL);
    for (int i = 0; i < 2; i++)
        display_button(window, &(buttons[i]), keys);
    return open;
}

text setup_score(env_t *env)
{
    text score_text;
    char *score = my_dec_to_base(env->c_game.player_stats.wave, "0123456789");
    char *score_final = malloc(sizeof(char) * (my_strlen(score) + 8));
    write_score_in_scoreboard(env);

    score_final = my_strcpy(score_final, "Score : ");
    score_final = my_strcat(score_final, score);
    free(score);
    score_text = setup_text(score_final, "font/o_drift.ttf", 75);
    sfText_setPosition(score_text.text, VC{758, 340});
    free(score_final);
    return (score_text);
}

void lose_menu(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    button *buttons = create_buttons_lose(env);
    text score = setup_score(env);
    text texte;

    if (env->langue[0] == 'E') {
        texte = setup_text("   Lose", "font/o_driftbold.ttf", 150);
    } else
        texte = setup_text(" Defaite", "font/o_driftbold.ttf", 150);
    sfText_setPosition(texte.text, VC{670, 200});
    while (sfRenderWindow_isOpen(window) && open) {
        open = render_loose_menu(window, keys, buttons, env);
        sfRenderWindow_drawText(window, texte.text, NULL);
        sfRenderWindow_drawText(window, score.text, NULL);
        update_mouse_cursor(window, mouse, env->tempo);
        sfRenderWindow_display(window);
    }
    free_lose_menu(texte, score, buttons);
    keys[sfKeyEscape] = 0;
}
