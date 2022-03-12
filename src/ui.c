/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ui
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "turrets.h"
#include "hud.h"
#include "ui.h"

void setup_popup_text(pop_button *bouton, turret_t turret, int i)
{
    char *e_cost = formating_hud(turret.energy_cost);
    char *e_per_s = formating_hud_in(turret.energy_per_s);
    char *s_cost = formating_hud(turret.steel_cost);
    char *s_per_s = formating_hud_in(turret.steel_per_s);

    bouton->titre = setup_text(turret.name, "font/Xero.ttf", 17);
    bouton->energy_cost = setup_text(e_cost , "font/Xero.ttf", 17);
    bouton->energy_per_s = setup_text(e_per_s , "font/Xero.ttf", 17);
    bouton->steel_cost = setup_text(s_cost, "font/Xero.ttf", 17);
    bouton->steel_per_s = setup_text(s_per_s, "font/Xero.ttf", 17);
    sfText_setPosition(bouton->titre.text, VC{i * 180 + 12, 840});
    sfText_setPosition(bouton->energy_cost.text, VC{i * 180 + 35, 980});
    sfText_setPosition(bouton->energy_per_s.text, VC{i * 180 + 35, 1020});
    sfText_setPosition(bouton->steel_cost.text, VC{i * 180 + 35, 1000});
    sfText_setPosition(bouton->steel_per_s.text, VC{i * 180 + 35, 1040});
    free(e_cost);
    free(e_per_s);
    free(s_cost);
    free(s_per_s);
}

pop_button *create_turret_button_ui(void)
{
    pop_button *button = NULL;
    turret_t *turrets = create_turret_type();
    sfVector2f scale;
    sfVector2f pos;
    int i = 0;

    for (i = 0; turrets[i].type != 0; i++);
    button = malloc(sizeof(pop_button) * (i + 1));
    for (i = 0; turrets[i].type != 0; i++) {
        setup_popup_text(&button[i], turrets[i], i);
        pos = VC{i * 180, 820};
        button[i].energy = create_object("img/Elecricity.png", VC{i * 180 + 12, 981}, VC{.05, .05});
        button[i].steel = create_object("img/steel.png", VC{i * 180 + 12, 1001}, VC{.05, .05});
        button[i].energy_income_pos = create_object("img/green_arrow.png", VC{i * 180 + 12, 1021}, VC{.05, .05});
        button[i].energy_income_neu = create_object("img/Neutral.png", VC{i * 180 + 12, 1021}, VC{.05, .05});
        button[i].energy_income_neg = create_object("img/red_arrow.png", VC{i * 180 + 12, 1021}, VC{.05, .05});
        button[i].steel_income_pos = create_object("img/green_arrow.png", VC{i * 180 + 12, 1041}, VC{.05, .05});
        button[i].steel_income_neu = create_object("img/Neutral.png", VC{i * 180 + 12, 1041}, VC{.05, .05});
        button[i].steel_income_neg = create_object("img/red_arrow.png", VC{i * 180 + 12, 1041}, VC{.05, .05});
        button[i].onglet = create_object("img/onglet.png", pos, VC{2, 2.2});
        pos = VC{i * 180 + 90, 900};
        scale = VC{.2, .2};
        button[i].icon = create_textured_object(turrets[i].texture, pos, scale);
        button[i].type = &(turrets[i]);
        sfSprite_setOrigin(button[i].icon.sprite, VC{150, 250});
        sfSprite_setRotation(button[i].icon.sprite, 90);
    }
    button[i].onglet.sprite = NULL;
    return button;
}

void display_turret_icon(pop_button *bu, sfRenderWindow *w, int i, sfVector2f p)
{
    sfColor dark = sfColor_fromRGBA(220, 220, 220, 150);

    if (pos_in_square(p, sfSprite_getGlobalBounds(bu[i].icon.sprite))) {
        sfSprite_setColor(bu[i].icon.sprite, dark);
        sfRenderWindow_drawSprite(w, bu[i].icon.sprite, NULL);
        sfSprite_setColor(bu[i].icon.sprite, sfWhite);
    } else {
        sfRenderWindow_drawSprite(w, bu[i].icon.sprite, NULL);
    }
}

void draw_text_ui(int stock, int cost, text text, sfRenderWindow *window)
{
    if (stock < cost) {
        sfText_setColor(text.text, sfRed);
        sfRenderWindow_drawText(window, text.text, NULL);
        sfText_setColor(text.text, sfWhite);
    } else {
        sfRenderWindow_drawText(window, text.text, NULL);
    }
}

void draw_correct_arrow(pop_button pop, sfRenderWindow *window)
{
    if (pop.type->energy_per_s > 0)
        sfRenderWindow_drawSprite(window, pop.energy_income_neg.sprite, NULL);
    if (pop.type->energy_per_s == 0)
        sfRenderWindow_drawSprite(window, pop.energy_income_neu.sprite, NULL);
    if (pop.type->energy_per_s < 0)
        sfRenderWindow_drawSprite(window, pop.energy_income_pos.sprite, NULL);
    if (pop.type->steel_per_s > 0)
        sfRenderWindow_drawSprite(window, pop.steel_income_neg.sprite, NULL);
    if (pop.type->steel_per_s == 0)
        sfRenderWindow_drawSprite(window, pop.steel_income_neu.sprite, NULL);
    if (pop.type->steel_per_s < 0)
        sfRenderWindow_drawSprite(window, pop.steel_income_pos.sprite, NULL);
}

void display_turrets_button_ui(pop_button *buttons, sfRenderWindow *window, int pickedup, env_t *env)
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
        sfRenderWindow_drawText(window, buttons[i].titre.text, NULL);
        sfRenderWindow_drawSprite(window, buttons[i].energy.sprite, NULL);
        sfRenderWindow_drawSprite(window, buttons[i].steel.sprite, NULL);
        draw_correct_arrow(buttons[i], window);
        draw_text_ui(env->c_game.player_stats.energy, buttons[i].type->energy_cost, buttons[i].energy_cost, window);
        draw_text_ui(env->c_game.player_stats.energy_income, buttons[i].type->energy_per_s, buttons[i].energy_per_s, window);
        draw_text_ui(env->c_game.player_stats.steel, buttons[i].type->steel_cost, buttons[i].steel_cost, window);
        draw_text_ui(env->c_game.player_stats.steel_income, buttons[i].type->steel_per_s, buttons[i].steel_per_s, window);
        if (pickedup != i)
            display_turret_icon(buttons, window, i, mouse_pos);
    }
}

int pickup_turrets(pop_button *but, sfVector2f mouse_pos, int pick, int *keys, env_t *env)
{
    if (pick == -1) {
        for (int i = 0; but[i].onglet.sprite != NULL; i++) {
            sfFloatRect rect = sfSprite_getGlobalBounds(but[i].icon.sprite);

            if (pos_in_square(mouse_pos, rect) && keys[leftMouse] == 1) {
                sfSprite_setPosition(but[i].icon.sprite, mouse_pos);
                return i;
            }
        }
    } else {
        sfVector2i coo = get_case_coords(mouse_pos);

        if (keys[leftMouse] == 2 || keys[leftMouse] == 1) {
            if (coo.x > 0 && coo.y > 0 && coo.x < 32 && coo.y < 18 && env->c_game.map[coo.y][coo.x].type == 0)
                sfSprite_setPosition(but[pick].icon.sprite, VC{coo.x * 60 + 30, coo.y * 60 + 30});
            else
                sfSprite_setPosition(but[pick].icon.sprite, mouse_pos);
            return pick;
        }
        if (keys[leftMouse] == 3 || keys[leftMouse] == 0) {
            if (coo.x < 32 && coo.y < 18 && env->c_game.map[coo.y][coo.x].type == 0) {
                clone_turret(env, but[pick].type, VC{coo.x, coo.y});
                env->c_game.map[coo.y][coo.x].type = 3;
            }
            sfSprite_setPosition(but[pick].icon.sprite, VC{pick * 180 + 90, sfSprite_getPosition(but[pick].onglet.sprite).y + 80});
            return -1;
        }
    }
    return -1;
}

void display_picked_turret(int pickedup, pop_button *buttons, sfRenderWindow *w)
{
    if (pickedup != -1) {
        sfColor darken = sfColor_fromRGBA(220, 220, 220, 150);
        sfColor normal = sfColor_fromRGBA(255, 255, 255, 255);

        sfSprite_setColor(buttons[pickedup].icon.sprite, darken);
        sfRenderWindow_drawSprite(w, buttons[pickedup].icon.sprite, NULL);
        sfSprite_setColor(buttons[pickedup].icon.sprite, normal);
    }
}
