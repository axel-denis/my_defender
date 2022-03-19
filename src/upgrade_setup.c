/*
** EPITECH PROJECT, 2022
** My_defender
** File description:
** upgrade_setup
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "turrets.h"
#include "hud.h"
#include "ui.h"
#include "button.h"

void set_menu_icons(upgrade_menu_t *menu)
{
    if (menu->upgrading->upgrade_1 == NULL)
        return;
    menu->icon_energy_1 =
        create_object("img/Elecricity.png", VC{340, 960}, VC{.12, .12});
    menu->icon_steel_1 =
        create_object("img/steel.png", VC{340, 1000}, VC{.12, .12});
    if (menu->upgrading->upgrade_2 == NULL)
        return;
    menu->icon_energy_2 =
        create_object("img/Elecricity.png", VC{1300, 960}, VC{.12, .12});
    menu->icon_steel_2 =
        create_object("img/steel.png", VC{1300, 1000}, VC{.12, .12});
}

void setup_opened_menu_up2(upgrade_menu_t *menu)
{
    if (menu->upgrading->upgrade_2 == NULL)
        return;
    sfText_setString(menu->cost_energy_2.text,
    formating_hud(menu->upgrading->upgrade_2->energy_cost));
    sfText_setPosition(menu->cost_energy_2.text, VC{1350, 955});
    sfText_setString(menu->cost_steel_2.text,
    formating_hud(menu->upgrading->upgrade_2->steel_cost));
    sfText_setPosition(menu->cost_steel_2.text, VC{1350 , 995});
    sfText_setString(menu->name_2.text, menu->upgrading->upgrade_2->name);
    sfText_setPosition(menu->name_2.text, VC{1440, 915});
    sfSprite_setScale(menu->upgrading->upgrade_2->sprite, VC{1.7, 1.7});
    sfSprite_setPosition(menu->upgrading->upgrade_2->sprite, VC{1440, 970});
}

void setup_opened_menu_up1(upgrade_menu_t *menu)
{
    if (menu->upgrading->upgrade_1 == NULL)
        return;
    sfText_setString(menu->cost_energy_1.text,
    formating_hud(menu->upgrading->upgrade_1->energy_cost));
    sfText_setPosition(menu->cost_energy_1.text, VC{390, 955});
    sfText_setString(menu->cost_steel_1.text,
    formating_hud(menu->upgrading->upgrade_1->steel_cost));
    sfText_setPosition(menu->cost_steel_1.text, VC{390, 995});
    sfText_setString(menu->name_1.text, menu->upgrading->upgrade_1->name);
    sfText_setPosition(menu->name_1.text, VC{480, 915});
    sfSprite_setScale(menu->upgrading->upgrade_1->sprite, VC{1.7, 1.7});
    sfSprite_setPosition(menu->upgrading->upgrade_1->sprite, VC{480, 970});
}

void display_colored_upgrades(SFWIN win, upgrade_menu_t menu)
{
    sfColor darken = sfColor_fromRGBA(200, 200, 200, 200);

    if (menu.upgrading->upgrade_1 != NULL &&
        pos_in_square(get_true_mouse_pos(win),
        sfSprite_getGlobalBounds(menu.upgrading->upgrade_1->sprite))
        == sfTrue) {
        sfSprite_setColor(menu.upgrading->upgrade_1->sprite, darken);
        sfRenderWindow_drawSprite(win, menu.upgrading->upgrade_1->sprite, NULL);
        sfSprite_setColor(menu.upgrading->upgrade_1->sprite, sfWhite);
    }
    if (menu.upgrading->upgrade_2 != NULL &&
        pos_in_square(get_true_mouse_pos(win),
        sfSprite_getGlobalBounds(menu.upgrading->upgrade_2->sprite))
        == sfTrue) {
        sfSprite_setColor(menu.upgrading->upgrade_2->sprite, darken);
        sfRenderWindow_drawSprite(win, menu.upgrading->upgrade_2->sprite, NULL);
        sfSprite_setColor(menu.upgrading->upgrade_2->sprite, sfWhite);
    }
}
