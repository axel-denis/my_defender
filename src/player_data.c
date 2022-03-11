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

void update_virgule_2(env_t *env)
{
    if (env->c_game.player_stats.steel.x
        + env->c_game.player_stats.steel.y * 0.1 > 0) {
        while (env->c_game.player_stats.steel.y > 9 ) {
            env->c_game.player_stats.steel.y -= 10;
            env->c_game.player_stats.steel.x += 1;
        }
        while (env->c_game.player_stats.steel.y < 0) {
            env->c_game.player_stats.steel.y += 10;
            env->c_game.player_stats.steel.x -= 1;
        }
    } else {
        while (env->c_game.player_stats.steel.y < -9) {
            env->c_game.player_stats.steel.y = 0;
            env->c_game.player_stats.steel.x -= 1;
        }
        while (env->c_game.player_stats.steel.y > 0) {
            env->c_game.player_stats.steel.y -= 10;
            env->c_game.player_stats.steel.x += 1;
        }
    }
}
void update_virgule_1(env_t *env)
{
    if (env->c_game.player_stats.energy.x
        + env->c_game.player_stats.energy.y * 0.1 > 0) {
        while (env->c_game.player_stats.energy.y > 9) {
            env->c_game.player_stats.energy.y -= 10;
            env->c_game.player_stats.energy.x += 1;
        }
        while (env->c_game.player_stats.energy.y < 0) {
            env->c_game.player_stats.energy.y += 10;
            env->c_game.player_stats.energy.x -= 1;
        }
    } else {
        while (env->c_game.player_stats.energy.y < -9) {
            env->c_game.player_stats.energy.y = 0;
            env->c_game.player_stats.energy.x -= 1;
        }
        while (env->c_game.player_stats.energy.y > 0) {
            env->c_game.player_stats.energy.y -= 10;
            env->c_game.player_stats.energy.x += 1;
        }
    }
}

void update_player_data(env_t *env, sfClock *clock)
{
    if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > 1) {
        env->c_game.player_stats.energy.x
        += env->c_game.player_stats.energy_income.x;
        env->c_game.player_stats.energy.y
        += env->c_game.player_stats.energy_income.y;
        env->c_game.player_stats.steel.x
        += env->c_game.player_stats.steel_income.x;
        env->c_game.player_stats.steel.y
        += env->c_game.player_stats.steel_income.y;
        update_virgule_1(env);
        update_virgule_2(env);
        sfClock_restart(clock);
    }
}
