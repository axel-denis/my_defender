/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ui_create
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
    sfText_setPosition(bouton->titre.text, VC{i * 180 + 12, 840 + 80});
    sfText_setPosition(bouton->energy_cost.text, VC{i * 180 + 35, 980 + 80});
    sfText_setPosition(bouton->energy_per_s.text, VC{i * 180 + 35, 1020 + 80});
    sfText_setPosition(bouton->steel_cost.text, VC{i * 180 + 35, 1000 + 80});
    sfText_setPosition(bouton->steel_per_s.text, VC{i * 180 + 35, 1040 + 80});
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
        pos = VC{i * 180, 900};
        button[i].energy = create_object("img/Elecricity.png", VC{i * 180 + 12, 981 + 80}, VC{.05, .05});
        button[i].steel = create_object("img/steel.png", VC{i * 180 + 12, 1001+ 80}, VC{.05, .05});
        button[i].energy_income_pos = create_object("img/green_arrow.png", VC{i * 180 + 12, 1021 + 80}, VC{.05, .05});
        button[i].energy_income_neu = create_object("img/Neutral.png", VC{i * 180 + 12, 1021 + 80}, VC{.05, .05});
        button[i].energy_income_neg = create_object("img/red_arrow.png", VC{i * 180 + 12, 1021 + 80}, VC{.05, .05});
        button[i].steel_income_pos = create_object("img/green_arrow.png", VC{i * 180 + 12, 1041 + 80}, VC{.05, .05});
        button[i].steel_income_neu = create_object("img/Neutral.png", VC{i * 180 + 12, 1041 + 80}, VC{.05, .05});
        button[i].steel_income_neg = create_object("img/red_arrow.png", VC{i * 180 + 12, 1041 + 80}, VC{.05, .05});
        button[i].onglet = create_object("img/onglet.png", pos, VC{2, 2.2});
        pos = VC{i * 180 + 90, 900 + 80};
        scale = VC{.2, .2};
        button[i].icon = create_textured_object(turrets[i].texture, pos, scale);
        button[i].type = &(turrets[i]);
        sfSprite_setOrigin(button[i].icon.sprite, VC{150, 250});
        sfSprite_setRotation(button[i].icon.sprite, 90);
    }
    button[i].onglet.sprite = NULL;
    return button;
}
