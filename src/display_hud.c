/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** hud
*/

#include "menu.h"
#include "enemy.h"
#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"
#include "maths.h"
#include "map.h"
#include "hud.h"

void display_hud_incomes(hud hud_p, env_t *env, sfRenderWindow *window)
{
    if (env->c_game.player_stats.steel_income > 0)
        sfRenderWindow_drawSprite(window,
            hud_p.icon_steel_income_pos.sprite, NULL);
    if (env->c_game.player_stats.steel_income == 0)
        sfRenderWindow_drawSprite(window,
            hud_p.icon_steel_income_neu.sprite, NULL);
    if (env->c_game.player_stats.steel_income < 0)
        sfRenderWindow_drawSprite(window,
            hud_p.icon_steel_income_neg.sprite, NULL);
    if (env->c_game.player_stats.energy_income > 0)
    sfRenderWindow_drawSprite(window,
        hud_p.icon_energy_income_pos.sprite, NULL);
    if (env->c_game.player_stats.energy_income == 0)
        sfRenderWindow_drawSprite(window,
            hud_p.icon_energy_income_neu.sprite, NULL);
    if (env->c_game.player_stats.energy_income < 0)
        sfRenderWindow_drawSprite(window,
            hud_p.icon_energy_income_neg.sprite, NULL);
}

void display_hud(hud hud_p, env_t *env, sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, hud_p.cadre.sprite, NULL);
    sfRenderWindow_drawSprite(window , hud_p.icon_health.sprite, NULL);
    sfRenderWindow_drawSprite(window , hud_p.icon_energy.sprite, NULL);
    sfRenderWindow_drawSprite(window , hud_p.icon_steel.sprite, NULL);
    display_hud_incomes(hud_p, env, window);
    sfRenderWindow_drawText(window, hud_p.text_health.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_energy.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_energy_income.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_steel.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_steel_income.text, NULL);
    sfRenderWindow_drawText(window, hud_p.wave.text, NULL);
}
