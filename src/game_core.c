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

game_data_t *create_gamedata(env_t *env)
{
    game_data_t *game_data = malloc(sizeof(game_data_t));

    create_game(env);
    game_data->enemies_type = create_enemies_type();
    game_data->wave = wave_create(env, game_data->enemies_type);
    game_data->upgrade = upgrade_create(env);
    game_data->clock = sfClock_create();
    env->c_game.wave_timer = sfClock_create();
    game_data->hud_player = create_hud();
    game_data->background = create_object("img/background.jpg",
        VC{0, 0}, VC{1, 1});
    game_data->worm_hole = create_object("img/icon.png", VC{
        env->c_game.starting_square.x * 60 - 5, env->c_game.starting_square.y
        * 60 - 58}, VC{.4, 1});
    game_data->worm_hole2 = create_object("img/icon2.png", VC{
        env->c_game.starting_square.x * 60 - 5, env->c_game.starting_square.y
        * 60 - 58}, VC{.4, 1});
    game_data->range = create_range();
    game_data->buttons = create_turret_button_ui(env);
    return game_data;
}

void game_displays(SFWIN window, game_data_t *g_data, env_t *env, int *pick)
{
    sfRenderWindow_drawSprite(window, g_data->background.sprite, NULL);
    display_map(env, window);
    display_hud(g_data->hud_player, env, window);
    sfRenderWindow_drawSprite(window, g_data->worm_hole.sprite, NULL);
    evolve_display_bullets(env, window);
    display_turret(window, env, g_data->range, get_true_mouse_pos(window));
    display_enemies(window, env);
    sfRenderWindow_drawSprite(window, g_data->worm_hole2.sprite, NULL);
    if (g_data->upgrade.upgrading == -1)
        display_turret_button_ui(g_data->buttons, window, *pick, env);
    upgrade_display(window, g_data->upgrade, env);
}

void game_updates(SFWIN window, game_data_t *g_data, env_t *env, int *pick)
{
    g_data->wave = wave_manage(env,
        g_data->enemies_type, g_data->wave);
    sfRenderWindow_clear(window, sfBlack);
    get_events(window, env->keys);
    upgrade_menu(env, window, &(g_data->upgrade), *pick);
    if (g_data->upgrade.upgrading == -1)
        *pick = pickup_turrets(g_data->buttons,
        get_true_mouse_pos(window), *pick, env);
    update_player_data(env, g_data->clock);
    update_hud(g_data->hud_player, env);
}

void game(sfRenderWindow *window, object mouse, env_t *env)
{
    if (error_handling() == 84)
        return;
    game_data_t *game_data = create_gamedata(env);
    int open = 1;
    int pick = -1;

    setmap_opacity(env);
    sfClock_restart(env->c_game.clock);
    while (sfRenderWindow_isOpen(window) && open) {
        game_updates(window, game_data, env, &pick);
        game_displays(window, game_data, env, &pick);
        display_picked_turret(pick, game_data->buttons, window);
        update_mouse_cursor(window, mouse, env->tempo);
        sfRenderWindow_display(window);

        evolve_all_enemies(env);
        open -= game_clock_gestion(env, window, mouse);
    }
    upgrade_destroy(game_data->upgrade);
    sfClock_destroy(game_data->clock);
    env->keys[sfKeyEscape] = 0;
}
