/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** main.c
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

void game(sfRenderWindow *window, object mouse, env_t *env)
{
    if (error_handling() == 84)
        return;
    create_game(env);
    enemy *enemies_type = create_enemies_type();
    wave_t wave = wave_create(env, enemies_type);
    int open = 1;
    int pick = -1;
    upgrade_menu_t upgrade = upgrade_create(env);
    sfClock *clock = sfClock_create();
    env->c_game.wave_timer = sfClock_create();
    hud hud_player = create_hud();
    object background = create_object("img/background.jpg", VC{0, 0}, VC{1, 1});
    object worm_hole = create_object("img/icon.png", VC{env->c_game.starting_square.x * 60 - 5, env->c_game.starting_square.y * 60 - 58}, VC{.4, 1});
    object worm_hole2 = create_object("img/icon2.png", VC{env->c_game.starting_square.x * 60 - 5, env->c_game.starting_square.y * 60 - 58}, VC{.4, 1});
    sfCircleShape *range = create_range();
    pop_button *buttons = create_turret_button_ui(env);

    setmap_opacity(env);
    sfClock_restart(env->c_game.clock);
    while (sfRenderWindow_isOpen(window) && open) {
        wave = wave_manage(env, enemies_type, wave);

        sfRenderWindow_clear(window, sfBlack);
        get_events(window, env->keys);
        upgrade_menu(env, window, &upgrade, pick);
        if (upgrade.upgrading == -1)
            pick = pickup_turrets(buttons, get_true_mouse_pos(window), pick, env);
        update_player_data(env, clock);
        update_hud(hud_player, env);

        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        display_map(env, window);
        display_hud(hud_player, env, window);
        sfRenderWindow_drawSprite(window, worm_hole.sprite, NULL);
        evolve_display_bullets(env, window);
        display_turret(window, env, range, get_true_mouse_pos(window));
        display_enemies(window, env);
        sfRenderWindow_drawSprite(window, worm_hole2.sprite, NULL);
        if (upgrade.upgrading == -1)
            display_turret_button_ui(buttons, window, pick, env);
        upgrade_display(window, upgrade, env);
        display_picked_turret(pick, buttons, window);
        update_mouse_cursor(window, mouse, env->tempo);
        sfRenderWindow_display(window);

        evolve_all_enemies(env);
        if (env->c_game.player_stats.health <= 0) {
            open = 0;
            lose_menu(window, mouse, env->keys, env);
            sfClock_restart(env->c_game.clock);
        }
        if (env->keys[sfKeyEscape] == 3) {
            if (pause_menu(window, mouse, env) == 1)
                open = 0;
            sfClock_restart(env->c_game.clock);
        }
        if (sfTime_asMilliseconds(sfClock_getElapsedTime(env->c_game.clock)) > 16)
            sfClock_restart(env->c_game.clock);
    }
    upgrade_destroy(upgrade);
    sfClock_destroy(clock);
    env->keys[sfKeyEscape] = 0;
}

sfRenderWindow *create_windows(env_t *env)
{
    sfImage *icon = sfImage_createFromFile("img/Elecricity.png");
    sfVector2u size = sfImage_getSize(icon);
    sfVideoMode main_w = {env->resolution, env->resolution / 16 * 9, 24};
    sfRenderWindow *window;

    if (env->screen_type == 0)
        window = sfRenderWindow_create(main_w, "My defender", 7, NULL);
    if (env->screen_type == 1)
        window = sfRenderWindow_create(main_w, "My defender", 1, NULL);
    if (env->screen_type == 2)
        window = sfRenderWindow_create(main_w, "My defender", 8, NULL);
    sfRenderWindow_setFramerateLimit(window, env->fps);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    sfRenderWindow_setVerticalSyncEnabled(window, env->vsync);
    sfRenderWindow_setIcon(window, size.x, size.y,  sfImage_getPixelsPtr(icon));
    sfImage_destroy(icon);
    return (window);
}

int main(void)
{
    object mouse = setup_mouse("img/cursor.png", VC{1.7, 1.7});
    env_t *env = create_env();
    env->keys = init_keys();
    sfRenderWindow *window = create_windows(env);

    main_menu(window, mouse, env);
    sfMusic_destroy(env->data.music);
    destroy_object(mouse);
    return (0);
}
