/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** create_hud.c
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

void set_hud_energy(hud *hud_object)
{
    hud_object->icon_energy =
        create_object("img/Elecricity.png", VC{1411, 85}, VC{.12, .12});
    hud_object->icon_energy_income_pos =
        create_object("img/green_arrow.png", VC{1661, 85}, VC{.12, .12});
    hud_object->icon_energy_income_neu =
        create_object("img/Neutral.png", VC{1661, 85}, VC{.12, .12});
    hud_object->icon_energy_income_neg =
        create_object("img/red_arrow.png", VC{1661, 85}, VC{.12, .12});
    hud_object->text_energy =
        setup_text("" , "font/o_drift.ttf", 45);
    sfText_setPosition(hud_object->text_energy.text, VC{1468, 75});
    hud_object->text_energy_income =
        setup_text("" , "font/o_drift.ttf", 45);
    sfText_setPosition(hud_object->text_energy_income.text,  VC{1718, 75});
}

void set_hud_steel(hud *hud_object)
{
    hud_object->icon_steel =
        create_object("img/steel.png", VC{1444, 147}, VC{.12, .12});
    hud_object->icon_steel_income_pos =
        create_object("img/green_arrow.png", VC{1661, 147}, VC{.12, .12});
    hud_object->icon_steel_income_neu =
        create_object("img/Neutral.png", VC{1661, 147}, VC{.12, .12});
    hud_object->icon_steel_income_neg =
        create_object("img/red_arrow.png", VC{1661, 147}, VC{.12, .12});
    hud_object->text_steel =
        setup_text("" , "font/o_drift.ttf", 45);
    sfText_setPosition(hud_object->text_steel.text, VC{1501, 137});
    hud_object->text_steel_income =
        setup_text("" , "font/o_drift.ttf", 45);
    sfText_setPosition(hud_object->text_steel_income.text, VC{1718, 137});
}

hud create_hud(void)
{
    hud hud_object;

    hud_object.icon_health = create_object("img/heart.png", VC{1373, 24}, VC{.12, .12});
    hud_object.text_health = setup_text("", "font/o_drift.ttf", 45);
    sfText_setPosition(hud_object.text_health.text, VC{1430, 14});
    set_hud_energy(&hud_object);
    set_hud_steel(&hud_object);
    hud_object.wave = setup_text("", "font/o_drift.ttf", 45);
    sfText_setPosition(hud_object.wave.text, VC{1670, 14});
    hud_object.cadre = create_object("img/blue_display.png", VC{1285, 5}, VC{1, 1});
    return (hud_object);
}
