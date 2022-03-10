/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** hud
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

void display_hud(hud hud_p, env_t *env, sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, hud_p.cadre.sprite, NULL);
    sfRenderWindow_drawSprite(window , hud_p.icon_health.sprite, NULL);
    sfRenderWindow_drawSprite(window , hud_p.icon_energy.sprite, NULL);
    sfRenderWindow_drawSprite(window , hud_p.icon_steel.sprite, NULL);
    if (env->c_game.player_stats.steel_income.x + env->c_game.player_stats.steel_income.y * 0.1 > 0)
        sfRenderWindow_drawSprite(window , hud_p.icon_steel_income_pos.sprite, NULL);
    if (env->c_game.player_stats.steel_income.x + env->c_game.player_stats.steel_income.y * 0.1 == 0)
        sfRenderWindow_drawSprite(window , hud_p.icon_steel_income_neu.sprite, NULL);
    if (env->c_game.player_stats.steel_income.x + env->c_game.player_stats.steel_income.y * 0.1 < 0)
        sfRenderWindow_drawSprite(window , hud_p.icon_steel_income_neg.sprite, NULL);
    if (env->c_game.player_stats.energy_income.x + env->c_game.player_stats.energy_income.y * 0.1 > 0)
    sfRenderWindow_drawSprite(window , hud_p.icon_energy_income_pos.sprite, NULL);
    if (env->c_game.player_stats.energy_income.x + env->c_game.player_stats.energy_income.y * 0.1 == 0)
        sfRenderWindow_drawSprite(window , hud_p.icon_energy_income_neu.sprite, NULL);
    if (env->c_game.player_stats.energy_income.x + env->c_game.player_stats.energy_income.y * 0.1 < 0)
    sfRenderWindow_drawSprite(window , hud_p.icon_energy_income_neg.sprite, NULL);
    sfRenderWindow_drawText(window, hud_p.text_health.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_energy.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_energy_income.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_steel.text, NULL);
    sfRenderWindow_drawText(window, hud_p.text_steel_income.text, NULL);
    sfRenderWindow_drawText(window, hud_p.wave.text, NULL);
}

hud create_hud(void)
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

char *formating_hud_in(sfVector2i value)
{
    char *text_val = my_dec_to_base(value.x, "0123456789");
    int absolute = ABS(value.y);
    char *text_abs = my_dec_to_base(absolute, "0123456789");
    int len =  + my_strlen(text_val) + (value.y < 0 && value.x >= 0);
    char *texte = malloc(sizeof(char) * (4 + my_strlen(text_abs) + len));

    if (value.y < 0 && value.x >= 0) {
        texte = my_strcpy(texte, "-");
        my_strcat(texte, text_val);
    } else
        texte = my_strcpy(texte, text_val);
    my_strcat(texte, ".");
    my_strcat(texte, text_abs);
    my_strcat(texte, "/s");
    free(text_val);
    free(text_abs);
    return (texte);
}

char *formating_hud(sfVector2i value)
{
    char *text_val = my_dec_to_base(value.x, "0123456789");
    int absolute = ABS(value.y);
    char *text_abs = my_dec_to_base(absolute, "0123456789");
    int len =  + my_strlen(text_val) + (value.y < 0 && value.x >= 0);
    char *texte = malloc(sizeof(char) * (2 + my_strlen(text_abs) + len));

    if (value.y < 0 && value.x >= 0) {
        texte = my_strcpy(texte, "-");
        my_strcat(texte, text_val);
    } else
        texte = my_strcpy(texte, text_val);
    my_strcat(texte, ".");
    my_strcat(texte, text_abs);
    free(text_val);
    free(text_abs);
    return (texte);
}

hud update_hud(hud hud_player, env_t *env)
{
    char *w_txt = my_dec_to_base(env->c_game.player_stats.wave, "0123456789");
    char *wave = malloc(sizeof(char) * (7 + (env->langue[0] == 'F') + my_strlen(w_txt)));
    char *energy = formating_hud(env->c_game.player_stats.energy);
    char *e_incom = formating_hud_in(env->c_game.player_stats.energy_income);
    char *steel = formating_hud(env->c_game.player_stats.steel);
    char *s_incom = formating_hud_in(env->c_game.player_stats.steel_income);

    sfText_setString(hud_player.text_health.text, my_nbr_to_str(env->c_game.player_stats.health));
    sfText_setString(hud_player.text_energy.text, energy);
    sfText_setString(hud_player.text_energy_income.text, e_incom);
    sfText_setString(hud_player.text_steel.text, steel);
    sfText_setString(hud_player.text_steel_income.text, s_incom);
    if (env->langue[0] == 'F') {
        wave = my_strcpy(wave, "Vague: ");
        my_strcat(wave,  w_txt);
    } else {
        wave = my_strcpy(wave, "Wave: ");
        my_strcat(wave, w_txt);
    }
    sfText_setString(hud_player.wave.text, wave);
    free(energy);
    free(e_incom);
    free(steel);
    free(s_incom);
    free(wave);
    free(w_txt);
    return (hud_player);
}
