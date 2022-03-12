/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** player_data
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "events.h"
#include "hud.h"

void update_player_data(env_t *env, sfClock *clock)
{
    if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > 1) {
        env->c_game.player_stats.energy
        += env->c_game.player_stats.energy_income;
        env->c_game.player_stats.steel += env->c_game.player_stats.steel_income;
        sfClock_restart(clock);
    }
}
