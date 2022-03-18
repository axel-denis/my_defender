/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** update_hud.c
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

void update_hud_playerstats(hud *hud_player, env_t *env)
{
    char *energy = formating_hud(env->c_game.player_stats.energy);
    char *e_incom = formating_hud_in(env->c_game.player_stats.energy_income);
    char *steel = formating_hud(env->c_game.player_stats.steel);
    char *s_incom = formating_hud_in(env->c_game.player_stats.steel_income);

    sfText_setString(hud_player->text_energy.text, energy);
    sfText_setString(hud_player->text_energy_income.text, e_incom);
    sfText_setString(hud_player->text_steel.text, steel);
    sfText_setString(hud_player->text_steel_income.text, s_incom);
    free(energy);
    free(e_incom);
    free(steel);
    free(s_incom);
}

hud update_hud(hud hud_player, env_t *env)
{
    char *w_txt = my_dec_to_base(env->c_game.player_stats.wave, "0123456789");
    char *wave = malloc(sizeof(char) * (7 + (env->langue[0] == 'F') + my_strlen(w_txt)));

    sfText_setString(hud_player.text_health.text,
        my_dec_to_base(env->c_game.player_stats.health, "0123456789"));
    update_hud_playerstats(&hud_player, env);
    if (env->langue[0] == 'F') {
        wave = my_strcpy(wave, "Vague: ");
        my_strcat(wave,  w_txt);
    } else {
        wave = my_strcpy(wave, "Wave: ");
        my_strcat(wave, w_txt);
    }
    sfText_setString(hud_player.wave.text, wave);
    free(wave);
    free(w_txt);
    return (hud_player);
}
