/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ui_display
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "turrets.h"
#include "hud.h"
#include "ui.h"

void display_turret_icon(pop_button *bu, sfRenderWindow *w, int i)
{
    sfColor dark = sfColor_fromRGBA(220, 220, 220, 150);
    sfVector2f p = get_true_mouse_pos(w);

    if (pos_in_square(p, sfSprite_getGlobalBounds(bu[i].icon.sprite))) {
        sfSprite_setColor(bu[i].icon.sprite, dark);
        sfRenderWindow_drawSprite(w, bu[i].icon.sprite, NULL);
        sfSprite_setColor(bu[i].icon.sprite, sfWhite);
    } else {
        sfRenderWindow_drawSprite(w, bu[i].icon.sprite, NULL);
    }
}

void display_picked_turret(int pickedup, pop_button *buttons, sfRenderWindow *w)
{
    if (pickedup != -1) {
        sfColor darken = sfColor_fromRGBA(220, 220, 220, 150);
        sfColor normal = sfColor_fromRGBA(255, 255, 255, 255);

        sfSprite_setColor(buttons[pickedup].icon.sprite, darken);
        sfRenderWindow_drawSprite(w, buttons[pickedup].icon.sprite, NULL);
        sfSprite_setColor(buttons[pickedup].icon.sprite, normal);
    }
}

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

    if (pos_in_square(mouse_pos, rect) == sfTrue && sfSprite_getPosition(but->onglet.sprite).y > 800) {
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

    if (pos_in_square(mouse_pos, rect) == sfFalse && sfSprite_getPosition(but->onglet.sprite).y < 900) {
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

void display_turrets_button_ui(pop_button *buttons, sfRenderWindow *window, int pickedup, env_t *env)
{
    for (int i = 0; buttons[i].onglet.sprite != NULL; i++) {
        move_up(window, &buttons[i]);
        move_down(window, &buttons[i]);
        sfRenderWindow_drawSprite(window, buttons[i].onglet.sprite, NULL);
        sfRenderWindow_drawText(window, buttons[i].titre.text, NULL);
        sfRenderWindow_drawSprite(window, buttons[i].energy.sprite, NULL);
        sfRenderWindow_drawSprite(window, buttons[i].steel.sprite, NULL);
        draw_correct_arrow(buttons[i], window);
        draw_text_ui(env->c_game.player_stats.energy,
        buttons[i].type->energy_cost, buttons[i].energy_cost, window);
        draw_text_ui(env->c_game.player_stats.energy_income,
        buttons[i].type->energy_per_s, buttons[i].energy_per_s, window);
        draw_text_ui(env->c_game.player_stats.steel,
        buttons[i].type->steel_cost, buttons[i].steel_cost, window);
        draw_text_ui(env->c_game.player_stats.steel_income,
        buttons[i].type->steel_per_s, buttons[i].steel_per_s, window);
        if (pickedup != i)
            display_turret_icon(buttons, window, i);
    }
}
