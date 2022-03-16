/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** player_data p
*/

#include "csfml.h"
#include "map.h"
#include "lib.h"
#include "structs.h"
#include "events.h"
#include "hud.h"
#include "enemy.h"

void create_game(env_t *env)
{
    env->c_game.player_stats.health = 100;
    env->c_game.player_stats.energy = 100;
    env->c_game.player_stats.steel = 100;
    env->c_game.player_stats.energy_income = 10;
    env->c_game.player_stats.steel_income = 10;
    env->c_game.player_stats.wave = 1;
    env->c_game.enemies = NULL;
    env->c_game.turrets = NULL;
    env->c_game.bullets = NULL;
    env->c_game.enemies = NULL;
    env->c_game.clock = sfClock_create();
    if (read_map(env, "map") == 1)
        my_errorstr("Error on map\n");
}

void update_player_data(env_t *env, sfClock *clock)
{
    if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > 1) {
        env->c_game.player_stats.energy
        += env->c_game.player_stats.energy_income;
        env->c_game.player_stats.steel += env->c_game.player_stats.steel_income;
        sfClock_restart(clock);
    }
}
