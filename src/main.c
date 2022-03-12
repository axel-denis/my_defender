/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** main.c
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
#include "turrets.h"
#include "ui.h"

sfCircleShape *create_range()
{
    sfCircleShape *range = sfCircleShape_create();

    sfCircleShape_setOutlineColor(range, sfColor_fromRGBA(200, 200, 200, 200));
    sfCircleShape_setOutlineThickness(range, 5);
    sfCircleShape_setFillColor(range, sfColor_fromRGBA(200, 200, 200, 50));
    sfCircleShape_setPosition(range, VC{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
    sfCircleShape_setRadius(range, WINDOW_HEIGHT / 2);
    sfCircleShape_setOrigin(range, VC{WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2});
    return (range);
}

void game(sfRenderWindow *window, object mouse, env_t *env)
{
    enemy *enemies = create_enemies_type();
    int open = 1;
    create_game(env);
    int pick = -1;
    sfClock *clock = sfClock_create();
    hud hud_player = create_hud();
    object background = create_object("img/background.jpg", VC{0, 0}, VC{1, 1});
    object worm_hole = create_object("img/icon.png", VC{env->c_game.starting_square.x * 60 , env->c_game.starting_square.y * 60 - 58}, VC{.3, 1});
    sfCircleShape *range = create_range();
    pop_button *buttons = create_turret_button_ui();

    setmap_opacity(env);
    sfClock_restart(env->c_game.clock);
    while (sfRenderWindow_isOpen(window) && open) {
        create_test_enemy(env, 75);
        /* Act */

        sfRenderWindow_clear(window, sfBlack);
        get_events(window, env->keys);
        pick = pickup_turrets(buttons, get_true_mouse_pos(window), pick, env);
        update_player_data(env, clock);
        update_hud(hud_player, env);

        /* Display */

        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        display_map(env, window);
        display_hud(hud_player, env, window);
        sfRenderWindow_drawSprite(window, worm_hole.sprite, NULL);
        display_turrets_button_ui(buttons, window, pick, env);
        display_turrets(window, env, range, get_true_mouse_pos(window));
        display_enemies(window, env);
        display_picked_turret(pick, buttons, window);
        update_mouse_cursor(window, mouse, env->tempo);
        sfRenderWindow_display(window);

        evolve_all_enemies(env);
        if (env->keys[sfKeyEscape] == 3) {
            if (pause_menu(window, mouse, env->keys, env) == 1)
                open = 0;
            sfClock_restart(env->c_game.clock);
        }

        if (sfTime_asMilliseconds(sfClock_getElapsedTime(env->c_game.clock)) > 16)
            sfClock_restart(env->c_game.clock);
    }
    sfClock_destroy(clock);
    env->keys[sfKeyEscape] = 0;
}

env_t *create_env(void)
{
    env_t *env = malloc(sizeof(env_t));

    env->tempo = sfClock_create();
    env->fps = 75;
    env->screen_type = 0;
    env->vsync = 1;
    env->resolution = 1920;
    env->data.music = sfMusic_createFromFile("sounds/uncharted-worlds.ogg");
    sfMusic_play(env->data.music);
    sfMusic_setLoop(env->data.music, sfTrue);
    env->volume = 100;
    sfMusic_setVolume(env->data.music, env->volume / 2);
    env->langue = my_strdup("FR");
    env->data.ground_texture =
        sfTexture_createFromFile("img/grass.png", NULL);
    env->data.path_texture = sfTexture_createFromFile("img/dirt.png", NULL);
    env->c_game.player_stats.wave = 1;
    env->c_game.enemies = NULL;
    env->c_game.turrets = NULL;
    env->c_game.clock = sfClock_create();
    return env;
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

// fix volume not modified on some buttons
// destroy everything
// cost working
// Coding syle
// Lose screen
