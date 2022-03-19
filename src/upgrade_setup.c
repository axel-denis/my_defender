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

void setup_opened_menu_up2(upgrade_menu_t *menu)
{
    float width;

    if (menu->upgrading->upgrade_2 == NULL)
        return;
    width = sfSprite_getGlobalBounds(menu->upgrading->upgrade_2->sprite).width;
    sfText_setString(menu->name_2.text, menu->upgrading->upgrade_2->name);
    sfText_setPosition(menu->name_2.text, VC{1440 - width, 900});
    sfSprite_setScale(menu->upgrading->upgrade_2->sprite, VC{2, 2});
    sfSprite_setPosition(menu->upgrading->upgrade_2->sprite, VC{1440 -
    width, 955});
}

void setup_opened_menu_up1(upgrade_menu_t *menu)
{
    if (menu->upgrading->upgrade_1 == NULL)
        return;
    sfText_setString(menu->name_1.text, menu->upgrading->upgrade_1->name);
    sfText_setPosition(menu->name_1.text, VC{480, 900});
    sfSprite_setScale(menu->upgrading->upgrade_1->sprite, VC{2, 2});
    sfSprite_setPosition(menu->upgrading->upgrade_1->sprite, VC{480, 955});
}
