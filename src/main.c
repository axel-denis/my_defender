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

turret create_turret_1(void)
{
    turret template;

    template.type = 1;
    template.sprite = sfSprite_create();
    template.texture = sfTexture_createFromFile("img/turret1_3.png", NULL);
    sfSprite_setTexture(template.sprite, template.texture, sfFalse);
    sfSprite_setScale(template.sprite, VC{.2, .2});
    sfSprite_setOrigin(template.sprite, VC{150, 250});
    template.position = VC{60 * 5 + 30, 60 * 5 + 30};
    sfSprite_setPosition(template.sprite, template.position);
    template.damage_speed = 2;
    template.damage_per_action = 1;
    return(template);
}

void update_player_data(env_t *env, sfClock *clock)
{
    if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > 1) {
        env->player_stats.energy.x += env->player_stats.energy_income.x;
        env->player_stats.energy.y += env->player_stats.energy_income.y;
        env->player_stats.steel.x += env->player_stats.steel_income.x;
        env->player_stats.steel.y += env->player_stats.steel_income.y;
        if (env->player_stats.energy.x + env->player_stats.energy.y * 0.1 > 0) {
            while (env->player_stats.energy.y > 9) {
                env->player_stats.energy.y -= 10;
                env->player_stats.energy.x += 1;
            }
            while (env->player_stats.energy.y < 0) {
                env->player_stats.energy.y += 10;
                env->player_stats.energy.x -= 1;
            }
        } else {
            while (env->player_stats.energy.y < -9) {
                env->player_stats.energy.y = 0;
                env->player_stats.energy.x -= 1;
            }
            while (env->player_stats.energy.y > 0) {
                env->player_stats.energy.y -= 10;
                env->player_stats.energy.x += 1;
            }
        }
        if (env->player_stats.steel.x + env->player_stats.steel.y * 0.1 > 0) {
            while (env->player_stats.steel.y > 9 ) {
                env->player_stats.steel.y -= 10;
                env->player_stats.steel.x += 1;
            }
            while (env->player_stats.steel.y < 0) {
                env->player_stats.steel.y += 10;
                env->player_stats.steel.x -= 1;
            }
        } else {
            while (env->player_stats.steel.y < -9) {
                env->player_stats.steel.y = 0;
                env->player_stats.steel.x -= 1;
            }
            while (env->player_stats.steel.y > 0) {
                env->player_stats.steel.y -= 10;
                env->player_stats.steel.x += 1;
            }
        }
        sfClock_restart(clock);
    }
}

pop_button *create_turret_button_ui(int nbr)
{
    pop_button *button = malloc(sizeof(pop_button) * (nbr + 1));

    for (int i = 0; i < nbr; i++) {
        button[i].titre = setup_text("Base Turret", "font/Xero.ttf", 15);
        button[i].onglet = create_object("img/onglet.png", VC{i * 180, 820}, VC{2, 2});
        button[i].icon = create_object("img/turret1_1.png", VC{i * 180 + 90, 900}, VC{0.2, 0.2});
        sfText_setPosition(button[i].titre.text, VC{i * 180 + 12, 840});
        sfSprite_setOrigin(button[i].icon.sprite, VC{150, 250});
        sfSprite_setRotation(button[i].icon.sprite, 90);
    }
    button[nbr].onglet.sprite = NULL;
    return button;
}

void display_turrets_button_ui(pop_button *buttons, sfRenderWindow *window)
{
    sfVector2f mouse_pos = get_true_mouse_pos(window);
    sfFloatRect rect;

    for (int i = 0; buttons[i].onglet.sprite != NULL; i++) {
        rect = sfSprite_getGlobalBounds(buttons[i].onglet.sprite);
        if (pos_in_square(mouse_pos, rect) == sfTrue && sfSprite_getPosition(buttons[i].onglet.sprite).y > 800) {
            sfSprite_move(buttons[i].onglet.sprite, VC{0, -1});
            sfSprite_move(buttons[i].icon.sprite, VC{0, -1});
            sfText_move(buttons[i].titre.text, VC{0, -1});
        }
        if (pos_in_square(mouse_pos, rect) == sfFalse && sfSprite_getPosition(buttons[i].onglet.sprite).y < 820) {
            sfSprite_move(buttons[i].onglet.sprite, VC{0, 1});
            sfSprite_move(buttons[i].icon.sprite, VC{0, 1});
            sfText_move(buttons[i].titre.text, VC{0, 1});
        }
        sfRenderWindow_drawSprite(window, buttons[i].onglet.sprite, NULL);
        if (pos_in_square(mouse_pos, sfSprite_getGlobalBounds(buttons[i].icon.sprite))) {
            sfSprite_setColor(buttons[i].icon.sprite, sfColor_fromRGB(150, 150, 150));
            sfRenderWindow_drawSprite(window, buttons[i].icon.sprite, NULL);
            sfSprite_setColor(buttons[i].icon.sprite, sfColor_fromRGB(255, 255, 255));
        } else {
            sfRenderWindow_drawSprite(window, buttons[i].icon.sprite, NULL);
        }
        sfRenderWindow_drawText(window, buttons[i].titre.text, NULL);
    }
}

void game(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    sfClock *clock = sfClock_create();
    hud hud_player = create_hud(env);
    object background = create_object("img/background.jpg", VC{0, 0}, VC{1, 1});
    object worm_hole = create_object("img/icon.png", VC{env->starting_square.x * 60 , env->starting_square.y * 60 - 58}, VC{.3, 1});
    turret tourelle = create_turret_1();
    pop_button *buttons = create_turret_button_ui(7);

    create_test_enemy(env, 100);
    create_test_enemy(env, 50);
    create_test_enemy(env, 75);
    setmap_opacity(env);
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        get_events(window, keys);
        printf("%d\n", keys[sfKeyA]);
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        //sfSprite_setRotation(tourelle.sprite, A_regarde_B(tourelle.position, sfSprite_getPosition(env->entities.enemies->next->next->sprite)));
        display_map(env, window);
        sfRenderWindow_drawSprite(window, tourelle.sprite, NULL);
        update_player_data(env, clock);
        update_hud(hud_player, env);
        display_hud(hud_player, env, window);
        sfRenderWindow_drawSprite(window, worm_hole.sprite, NULL);
        display_turrets_button_ui(buttons, window);
        display_enemies(window, env);
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
        if (keys[sfKeyEscape] == 3) {
            if (pause_menu(window, mouse, keys, env) == 1)
                open = 0;
        }
        evolve_all_enemies(env);
    }
    sfClock_destroy(clock);
    keys[sfKeyEscape] = 0;
}

env_t *create_env(void)
{
    env_t *env = malloc(sizeof(env_t));

    env->fps = 75;
    env->player_stats.health = 100;
    env->player_stats.energy.x = -200;
    env->player_stats.energy.y = 0;
    env->player_stats.steel.x = -10;
    env->player_stats.steel.y = -5;
    env->player_stats.energy_income.x = 2;
    env->player_stats.energy_income.y = 5;
    env->player_stats.steel_income.x = 0;
    env->player_stats.steel_income.y = 1;
    env->data.music = sfMusic_createFromFile("sounds/uncharted-worlds.ogg");
    sfMusic_play(env->data.music);
    sfMusic_setLoop(env->data.music, sfTrue);
    env->volume = 100;
    sfMusic_setVolume(env->data.music, env->volume / 2);
    env->langue = my_strdup("EN");
    env->data.ground_texture =
        sfTexture_createFromFile("img/grass.png", NULL);
    env->data.path_texture = sfTexture_createFromFile("img/dirt.png", NULL);
    env->player_stats.wave = 1;
    env->entities.enemies = NULL;
    return env;
}

int main(void)
{
    int *keys = init_keys();
    sfVideoMode main_w = {1920, 1080, 64};
    sfRenderWindow *window;
    object mouse = setup_mouse("img/cursor.png", VC{1.7, 1.7});
    env_t *env = create_env();

    window = sfRenderWindow_create(main_w, "My defender", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, env->fps);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    if (read_map(env, "map") == 1) {
        my_errorstr("Error on map\n");
        return 84;
    }
    main_menu(window, mouse, keys, env);
    sfMusic_destroy(env->data.music);
    destroy_object(mouse);
    return (0);
}

// Coding syle
// Lose screen
// Pick up turrets
