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

char *formating_hud_in(int value)
{
    char *text_val = my_dec_to_base(value / 10, "0123456789");
    char *text_abs = my_dec_to_base(ABS(value % 10), "0123456789");
    int len =  + my_strlen(text_val);
    char *texte = malloc(sizeof(char) * (4 + my_strlen(text_abs) + len));

    texte = my_strcpy(texte, text_val);
    my_strcat(texte, ".");
    my_strcat(texte, text_abs);
    my_strcat(texte, "/s");
    free(text_val);
    free(text_abs);
    return (texte);
}

char *formating_hud(int value)
{
    char *text_val = my_dec_to_base(value / 10, "0123456789");
    char *text_abs = my_dec_to_base(ABS(value % 10), "0123456789");
    int len =  + my_strlen(text_val);
    char *texte = malloc(sizeof(char) * (2 + my_strlen(text_abs) + len));

    texte = my_strcpy(texte, text_val);
    my_strcat(texte, ".");
    my_strcat(texte, text_abs);
    free(text_val);
    free(text_abs);
    return (texte);
}

hud update_hud(hud hud_player, env_t *env)
{
    char *w_txt = my_dec_to_base(env->c_game.player_stats.wave, "0123456789");
    char *wave = malloc(sizeof(char) * (7 + (env->langue[0] == 'F') + my_strlen(w_txt)));
    char *energy = formating_hud(env->c_game.player_stats.energy);
    char *e_incom = formating_hud_in(env->c_game.player_stats.energy_income);
    char *steel = formating_hud(env->c_game.player_stats.steel);
    char *s_incom = formating_hud_in(env->c_game.player_stats.steel_income);

    sfText_setString(hud_player.text_health.text, my_dec_to_base(env->c_game.player_stats.health, "0123456789"));
    sfText_setString(hud_player.text_energy.text, energy);
    sfText_setString(hud_player.text_energy_income.text, e_incom);
    sfText_setString(hud_player.text_steel.text, steel);
    sfText_setString(hud_player.text_steel_income.text, s_incom);
    if (env->langue[0] == 'F') {
        wave = my_strcpy(wave, "Vague: ");
        my_strcat(wave,  w_txt);
    } else {
        wave = my_strcpy(wave, "Wave: ");
        my_strcat(wave, w_txt);
    }
    sfText_setString(hud_player.wave.text, wave);
    free(energy);
    free(e_incom);
    free(steel);
    free(s_incom);
    free(wave);
    free(w_txt);
    return (hud_player);
}
