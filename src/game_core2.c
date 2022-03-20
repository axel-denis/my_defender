/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** game_core.c
*/

#include "error_handling.h"
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
#include "turrets.h"
#include "ui.h"
#include "bullets.h"
#include "env.h"
#include "range.h"

int game_clock_gestion(env_t *env, SFWIN window, object mouse)
{
    int close = 0;

    if (env->c_game.player_stats.health <= 0) {
        close = 1;
        lose_menu(window, mouse, env->keys, env);
        sfClock_restart(env->c_game.clock);
    }
    if (env->keys[sfKeyEscape] == 3) {
        if (pause_menu(window, mouse, env) == 1)
            close = 1;
        sfClock_restart(env->c_game.clock);
    }
    if (sfTime_asMilliseconds(sfClock_getElapsedTime(env->c_game.clock)) > 16)
        sfClock_restart(env->c_game.clock);
    return close;
}

void create_base_game_data(env_t *env, game_data_t *game_data)
{
    game_data->enemies_type = create_enemies_type();
    game_data->wave = wave_create(env, game_data->enemies_type);
    game_data->upgrade = upgrade_create(env);
    game_data->clock = sfClock_create();
    env->c_game.wave_timer = sfClock_create();
    game_data->hud_player = create_hud();
}
