/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** wave_manager
*/

#include "enemy.h"
#include "csfml.h"
#include "lib.h"
#include "structs.h"

wave_t wave_manage(env_t *env, enemy *enemies_type, wave_t current_wave)
{
    if (current_wave.nbr1 == 0 && current_wave.nbr2 == 0) {
        env->c_game.player_stats.wave += 1;
        sfClock_restart(env->c_game.wave_timer);
        return (wave_create(env, enemies_type));
    }
    if (sfTime_asSeconds(sfClock_getElapsedTime(env->c_game.wave_timer)) >
        0.5 / env->c_game.player_stats.wave) {
        sfClock_restart(env->c_game.wave_timer);
        if (current_wave.nbr1 > 0) {
            clone_enemy(env, enemies_type[current_wave.type1]);
            current_wave.nbr1 -= 1;
        } else {
            clone_enemy(env, enemies_type[current_wave.type2]);
            current_wave.nbr2 -= 1;
        }
    }
    return (current_wave);
}
