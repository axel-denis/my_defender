/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ui_display c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "turrets.h"
#include "hud.h"
#include "ui.h"

void draw_text_ui(int stock, int cost, text text, sfRenderWindow *window)
{
    if (stock < cost) {
        sfText_setColor(text.text, sfRed);
        sfRenderWindow_drawText(window, text.text, NULL);
        sfText_setColor(text.text, sfWhite);
    } else {
        sfRenderWindow_drawText(window, text.text, NULL);
    }
}

void draw_correct_arrow(pop_button pop, sfRenderWindow *window)
{
    if (pop.type->energy_per_s > 0)
        sfRenderWindow_drawSprite(window, pop.energy_income_neg.sprite, NULL);
    if (pop.type->energy_per_s == 0)
        sfRenderWindow_drawSprite(window, pop.energy_income_neu.sprite, NULL);
    if (pop.type->energy_per_s < 0)
        sfRenderWindow_drawSprite(window, pop.energy_income_pos.sprite, NULL);
    if (pop.type->steel_per_s > 0)
        sfRenderWindow_drawSprite(window, pop.steel_income_neg.sprite, NULL);
    if (pop.type->steel_per_s == 0)
        sfRenderWindow_drawSprite(window, pop.steel_income_neu.sprite, NULL);
    if (pop.type->steel_per_s < 0)
        sfRenderWindow_drawSprite(window, pop.steel_income_pos.sprite, NULL);
}

void move_up(sfRenderWindow *window, pop_button *but)
{
    sfVector2f mouse_pos = get_true_mouse_pos(window);
    sfFloatRect rect = sfSprite_getGlobalBounds(but->onglet.sprite);

    if (HOVER && sfSprite_getPosition(but->onglet.sprite).y > 830) {
        sfSprite_move(but->onglet.sprite, VC{0, -4});
        sfSprite_move(but->icon.sprite, VC{0, -4});
        sfSprite_move(but->energy_income_neg.sprite, VC{0, -4});
        sfSprite_move(but->energy_income_neu.sprite, VC{0, -4});
        sfSprite_move(but->energy_income_pos.sprite, VC{0, -4});
        sfSprite_move(but->steel_income_neg.sprite, VC{0, -4});
        sfSprite_move(but->steel_income_neu.sprite, VC{0, -4});
        sfSprite_move(but->steel_income_pos.sprite, VC{0, -4});
        sfSprite_move(but->energy.sprite, VC{0, -4});
        sfSprite_move(but->steel.sprite, VC{0, -4});
        sfText_move(but->energy_cost.text, VC{0, -4});
        sfText_move(but->steel_cost.text, VC{0, -4});
        sfText_move(but->energy_per_s.text, VC{0, -4});
        sfText_move(but->steel_per_s.text, VC{0, -4});
        sfText_move(but->titre.text, VC{0, -4});
    }
}

void move_down(sfRenderWindow *window, pop_button *but)
{
    sfVector2f mouse_pos = get_true_mouse_pos(window);
    sfFloatRect rect = sfSprite_getGlobalBounds(but->onglet.sprite);

    if (NOT_HOVER && sfSprite_getPosition(but->onglet.sprite).y < 920) {
        sfSprite_move(but->onglet.sprite, VC{0, 4});
        sfSprite_move(but->icon.sprite, VC{0, 4});
        sfSprite_move(but->energy_income_neg.sprite, VC{0, 4});
        sfSprite_move(but->energy_income_neu.sprite, VC{0, 4});
        sfSprite_move(but->energy_income_pos.sprite, VC{0, 4});
        sfSprite_move(but->steel_income_neg.sprite, VC{0, 4});
        sfSprite_move(but->steel_income_neu.sprite, VC{0, 4});
        sfSprite_move(but->steel_income_pos.sprite, VC{0, 4});
        sfSprite_move(but->energy.sprite, VC{0, 4});
        sfSprite_move(but->steel.sprite, VC{0, 4});
        sfText_move(but->energy_cost.text, VC{0, 4});
        sfText_move(but->steel_cost.text, VC{0, 4});
        sfText_move(but->energy_per_s.text, VC{0, 4});
        sfText_move(but->steel_per_s.text, VC{0, 4});
        sfText_move(but->titre.text, VC{0, 4});
    }
}

void display_turret_button_ui(pop_button *but, SFWIN win, int pick, env_t *env)
{
    for (int i = 0; but[i].onglet.sprite != NULL; i++) {
        move_up(win, &but[i]);
        move_down(win, &but[i]);
        sfRenderWindow_drawSprite(win, but[i].onglet.sprite, NULL);
        sfRenderWindow_drawText(win, but[i].titre.text, NULL);
        sfRenderWindow_drawSprite(win, but[i].energy.sprite, NULL);
        sfRenderWindow_drawSprite(win, but[i].steel.sprite, NULL);
        draw_correct_arrow(but[i], win);
        draw_text_ui(env->c_game.player_stats.energy,
        but[i].type->energy_cost, but[i].energy_cost, win);
        draw_text_ui(env->c_game.player_stats.energy_income,
        but[i].type->energy_per_s, but[i].energy_per_s, win);
        draw_text_ui(env->c_game.player_stats.steel,
        but[i].type->steel_cost, but[i].steel_cost, win);
        draw_text_ui(env->c_game.player_stats.steel_income,
        but[i].type->steel_per_s, but[i].steel_per_s, win);
        if (pick != i)
            display_turret_icon(but, win, i);
    }
}
