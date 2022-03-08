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

void display_hud(hud hud_p, env_t *env, sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, hud_p.cadre.sprite, NULL);
    sfRenderWindow_drawSprite(window , hud_p.icon_health.sprite, NULL);
    sfRenderWindow_drawSprite(window , hud_p.icon_energy.sprite, NULL);
    sfRenderWindow_drawSprite(window , hud_p.icon_steel.sprite, NULL);
    if (env->player_stats.steel_income.x + env->player_stats.steel_income.y * 0.1 > 0)
        sfRenderWindow_drawSprite(window , hud_p.icon_steel_income_pos.sprite, NULL);
    if (env->player_stats.steel_income.x + env->player_stats.steel_income.y * 0.1 == 0)
        sfRenderWindow_drawSprite(window , hud_p.icon_steel_income_neu.sprite, NULL);
    if (env->player_stats.steel_income.x + env->player_stats.steel_income.y * 0.1 < 0)
        sfRenderWindow_drawSprite(window , hud_p.icon_steel_income_neg.sprite, NULL);
    if (env->player_stats.energy_income.x + env->player_stats.energy_income.y * 0.1 > 0)
    sfRenderWindow_drawSprite(window , hud_p.icon_energy_income_pos.sprite, NULL);
    if (env->player_stats.energy_income.x + env->player_stats.energy_income.y * 0.1 == 0)
        sfRenderWindow_drawSprite(window , hud_p.icon_energy_income_neu.sprite, NULL);
    if (env->player_stats.energy_income.x + env->player_stats.energy_income.y * 0.1 < 0)
    sfRenderWindow_drawSprite(window , hud_p.icon_energy_income_neg.sprite, NULL);
    sfRenderWindow_drawText(window, hud_p.text_health.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_energy.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_energy_income.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_steel.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_steel_income.text, NULL);
    sfRenderWindow_drawText(window, hud_p.wave.text, NULL);
}

hud create_hud(env_t *env)
{
    hud h_p;

    h_p.icon_health = create_object("img/heart.png", VC{1373, 24}, VC{.12, .12});
    h_p.text_health = setup_text("", "font/o_drift.ttf", 45);
    sfText_setPosition(h_p.text_health.text, VC{1430, 14});
    h_p.icon_energy = create_object("img/Elecricity.png", VC{1411, 85}, VC{.12, .12});
    h_p.icon_energy_income_pos = create_object("img/green_arrow.png", VC{1661, 85}, VC{.12, .12});
    h_p.icon_energy_income_neu = create_object("img/Neutral.png", VC{1661, 85}, VC{.12, .12});
    h_p.icon_energy_income_neg = create_object("img/red_arrow.png", VC{1661, 85}, VC{.12, .12});
    h_p.text_energy = setup_text("" , "font/o_drift.ttf", 45);
    sfText_setPosition(h_p.text_energy.text, VC{1468, 75});
    h_p.text_energy_income = setup_text("" , "font/o_drift.ttf", 45);
    sfText_setPosition(h_p.text_energy_income.text,  VC{1718, 75});
    h_p.icon_steel = create_object("img/Metal.png", VC{1444, 147}, VC{.12, .12});
    h_p.icon_steel_income_pos = create_object("img/green_arrow.png", VC{1661, 147}, VC{.12, .12});
    h_p.icon_steel_income_neu = create_object("img/Neutral.png", VC{1661, 147}, VC{.12, .12});
    h_p.icon_steel_income_neg = create_object("img/red_arrow.png", VC{1661, 147}, VC{.12, .12});
    h_p.text_steel = setup_text("" , "font/o_drift.ttf", 45);
    sfText_setPosition(h_p.text_steel.text, VC{1501, 137});
    h_p.text_steel_income = setup_text("" , "font/o_drift.ttf", 45);
    sfText_setPosition(h_p.text_steel_income.text, VC{1718, 137});
    h_p.wave = setup_text("", "font/o_drift.ttf", 45);
    sfText_setPosition(h_p.wave.text, VC{1670, 14});
    h_p.cadre = create_object("img/blue_display.png", VC{1285, 5}, VC{1, 1});
    return (h_p);
}

void update_player_data(env_t *env, sfClock *clock)
{
    if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > 1) {
        env->player_stats.energy.x += env->player_stats.energy_income.x;
        env->player_stats.steel.x += env->player_stats.steel_income.x;
        env->player_stats.energy.y += env->player_stats.energy_income.y;
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

char *formating_hud(sfVector2i value)
{
    char *texte;
    int absolute_value = ABS(value.y);

    if (value.y < 0 && value.x >= 0) {
        texte = my_strdup("-");
        my_strcat(texte, my_dec_to_base(value.x, "0123456789"));
    } else
        texte = my_dec_to_base(value.x, "0123456789");
    my_strcat(texte, ".");
    my_strcat(texte, my_dec_to_base(absolute_value, "0123456789"));
    return (texte);
}

hud update_hud(hud hud_player, env_t *env)
{
    char *wave;
    char *energy = formating_hud(env->player_stats.energy);
    char *e_incom = formating_hud(env->player_stats.energy_income);
    char *steel = formating_hud(env->player_stats.steel);
    char *s_incom = formating_hud(env->player_stats.steel_income);

    my_strcat(e_incom, "/s");
    my_strcat(s_incom, "/s");
    sfText_setString(hud_player.text_health.text, my_nbr_to_str(env->player_stats.health));
    sfText_setString(hud_player.text_energy.text, energy);
    sfText_setString(hud_player.text_energy_income.text, e_incom);
    sfText_setString(hud_player.text_steel.text, steel);
    sfText_setString(hud_player.text_steel_income.text, s_incom);
    if (env->langue[0] == 'F') {
        wave = my_strdup("Vague: ");
        my_strcat(wave,  my_dec_to_base(env->player_stats.wave, "0123456789"));
        sfText_setString(hud_player.wave.text, wave);
    } else {
        wave = my_strdup("Wave: ");
        my_strcat(wave, my_dec_to_base(env->player_stats.wave, "0123456789"));
        sfText_setString(hud_player.wave.text, wave);
    }
    free(energy);
    free(e_incom);
    free(steel);
    free(s_incom);
    free(wave);
    return (hud_player);
}

void game(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    sfClock *clock = sfClock_create();
    hud hud_player = create_hud(env);
    object background = create_object("img/background.jpg", VC{0, 0}, VC{1, 1});
    object worm_hole = create_object("img/icon.png", VC{env->starting_square.x * 60 , env->starting_square.y * 60 - 58}, VC{.3, 1});
    turret tourelle = create_turret_1();
    object button1 = create_object("img/Blue_button.png", VC{50, 836 - 20}, VC{0.3, 0.3});

    create_enemy_type_1(env);
    create_enemy_type_1(env);
    create_enemy_type_1(env);
    setmap_opacity(env);
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        sfSprite_setRotation(tourelle.sprite, A_regarde_B(tourelle.position, sfSprite_getPosition(env->enemies->next->next->sprite)));
        display_map(env, window);
        sfRenderWindow_drawSprite(window, tourelle.sprite, NULL);
        update_player_data(env, clock);
        update_hud(hud_player, env);
        display_hud(hud_player, env, window);
        sfRenderWindow_drawSprite(window, button1.sprite, NULL);
        sfRenderWindow_drawSprite(window, worm_hole.sprite, NULL);
        display_enemies(window, env);
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
        evolve_all_enemies(env);
    }
    sfClock_destroy(clock);
    keys[sfKeyEscape] = 0;
}

env_t *create_env(void)
{
    env_t *env = malloc(sizeof(env_t));

    env->player_stats.health = 100;
    env->player_stats.energy.x = -200;
    env->player_stats.energy.y = 0;
    env->player_stats.steel.x = -10;
    env->player_stats.steel.y = 5;
    env->player_stats.energy_income.x = 2;
    env->player_stats.energy_income.y = 5;
    env->player_stats.steel_income.x = 0;
    env->player_stats.steel_income.y = 0;
    env->data.music = sfMusic_createFromFile("sounds/uncharted-worlds.ogg");
    sfMusic_play(env->data.music);
    sfMusic_setLoop(env->data.music, sfTrue);
    env->volume = 0;
    sfMusic_setVolume(env->data.music, env->volume);
    env->langue = my_strdup("EN");
    env->data.ground_texture =
        sfTexture_createFromFile("img/grass.png", NULL);
    env->data.path_texture = sfTexture_createFromFile("img/dirt.png", NULL);
    env->player_stats.wave = 1;
    env->enemies = NULL;
    return env;
}

int main(void)
{
    int *keys = init_keys();
    sfVideoMode main_w = {1920, 1080, 64};
    sfRenderWindow *window;
    object mouse = setup_mouse("img/cursor.png", VC{0.05, 0.05});
    env_t *env = create_env();

    window = sfRenderWindow_create(main_w, "My defender", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 75);
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
