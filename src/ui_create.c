/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ui_create c
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
    char *e_per_s = formating_hud(turret.energy_per_s);
    char *s_cost = formating_hud(turret.steel_cost);
    char *s_per_s = formating_hud(turret.steel_per_s);

    bouton->titre = setup_text(turret.name, "font/Xero.ttf", 17);
    bouton->energy_cost = setup_text(e_cost , "font/Xero.ttf", 17);
    bouton->energy_per_s = setup_text(e_per_s , "font/Xero.ttf", 17);
    bouton->steel_cost = setup_text(s_cost, "font/Xero.ttf", 17);
    bouton->steel_per_s = setup_text(s_per_s, "font/Xero.ttf", 17);
    sfText_setPosition(bouton->titre.text, VC{i * 180 + 12, 840 + 100});
    sfText_setPosition(bouton->energy_cost.text, VC{i * 180 + 35, 980 + 100});
    sfText_setPosition(bouton->energy_per_s.text, VC{i * 180 + 35, 1020 + 100});
    sfText_setPosition(bouton->steel_cost.text, VC{i * 180 + 35, 1000 + 100});
    sfText_setPosition(bouton->steel_per_s.text, VC{i * 180 + 35, 1040 + 100});
    free(e_cost);
    free(e_per_s);
    free(s_cost);
    free(s_per_s);
}

void create_icons(pop_button *but, int i)
{
    but->energy = create_object("img/Elecricity.png",
        VC{i * 180 + 12, 1001 + 80}, VC{.05, .05});
    but->steel = create_object("img/steel.png",
        VC{i * 180 + 12, 1021+ 80}, VC{.05, .05});
    but->energy_income_pos = create_object("img/green_arrow.png",
        VC{i * 180 + 12, 1121}, VC{.05, .05});
    but->energy_income_neu = create_object("img/Neutral.png",
        VC{i * 180 + 12, 1121}, VC{.05, .05});
    but->energy_income_neg = create_object("img/red_arrow.png",
        VC{i * 180 + 12, 1121}, VC{.05, .05});
    but->steel_income_pos = create_object("img/green_arrow.png",
        VC{i * 180 + 12, 1061 + 80}, VC{.05, .05});
    but->steel_income_neu = create_object("img/Neutral.png",
        VC{i * 180 + 12, 1061 + 80}, VC{.05, .05});
    but->steel_income_neg = create_object("img/red_arrow.png",
        VC{i * 180 + 12, 1061 + 80}, VC{.05, .05});
}

pop_button *create_turret_button_ui(env_t *env)
{
    pop_button *button = NULL;
    turret_t *turrets = create_turret_type(env);
    int i = 0;

    for (i = 0; turrets[i].type != 0; i++);
    button = malloc(sizeof(pop_button) * (i + 1));
    for (i = 0; turrets[i].type != 0; i++) {
        setup_popup_text(&button[i], turrets[i], i);
        button[i].onglet = create_object("img/onglet.png", VC{i * 180, 920},
        VC{2, 2.2});
        create_icons(&button[i], i);
        button[i].icon = create_textured_object(turrets[i].texture,
        VC{i * 180 + 90, 920 + 80}, VC{.2, .2});
        button[i].type = &(turrets[i]);
        sfSprite_setOrigin(button[i].icon.sprite, VC{150, 270});
        sfSprite_setRotation(button[i].icon.sprite, 90);
    }
    button[i].onglet.sprite = NULL;
    return button;
}
