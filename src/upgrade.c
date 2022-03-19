/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** upgrade
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "turrets.h"
#include "hud.h"
#include "ui.h"
#include "button.h"

void upgrade_menu_open(env_t *env, SFWIN window, upgrade_menu_t *menu, int pick)
{
    turret_t *actual = env->c_game.turrets;

    while (actual != NULL) {
        if (actual->type == 0) {
            actual = actual->next;
            continue;
        }
        if (env->keys[leftMouse] == 3 &&
            pos_in_square(get_true_mouse_pos(window),
            sfSprite_getGlobalBounds(actual->sprite)) == sfTrue && pick == -1) {
            menu->upgrading = actual;
            setup_opened_menu_up1(menu);
            setup_opened_menu_up2(menu);
            set_menu_icons(menu);
        }
        actual = actual->next;
    }
}

void upgrade_menu(env_t *env, SFWIN window, upgrade_menu_t *menu, int pick)
{
    sfVector2f pos = get_true_mouse_pos(window);

    if (menu->upgrading == NULL)
        upgrade_menu_open(env, window, menu, pick);
    else {
        if (env->keys[leftMouse] == 3 && pos_in_square(pos,
            sfSprite_getGlobalBounds(menu->close.sprite)) == sfTrue)
            menu->upgrading = NULL;
        if (menu->upgrading != NULL && menu->upgrading->upgrade_1 != NULL &&
            pos_in_square(pos,
            sfSprite_getGlobalBounds(menu->upgrading->upgrade_1->sprite))
            == sfTrue && env->keys[leftMouse] == 3) {
            menu->upgrading = NULL;
            upgrade_turret(env, find_turret_by_pos(env, pos), 1);
            }
        if (menu->upgrading != NULL && menu->upgrading->upgrade_2 != NULL &&
            pos_in_square(pos,
            sfSprite_getGlobalBounds(menu->upgrading->upgrade_2->sprite))
            == sfTrue && env->keys[leftMouse] == 3) {
            menu->upgrading = NULL;
            upgrade_turret(env, find_turret_by_pos(env, pos), 2);
            }
    }
    return;
}

upgrade_menu_t upgrade_create(env_t *env)
{
    upgrade_menu_t upgrade;

    upgrade.upgrading = NULL;
    upgrade.back = create_object("img/panel.png", VC{-3, 900}, VC{1.259, 1});
    upgrade.close = create_button(VC{.1, .1}, VC{1850, 920}, sfFalse);
    upgrade.name_1 = setup_text("", "font/o_driftbold.ttf", 40);
    upgrade.name_2 = setup_text("", "font/o_driftbold.ttf", 40);
    upgrade.cost_energy_1 = setup_text("", "font/o_drift.ttf", 35);
    upgrade.cost_steel_1 = setup_text("", "font/o_drift.ttf", 35);
    upgrade.cost_energy_2 = setup_text("", "font/o_drift.ttf", 35);
    upgrade.cost_steel_2 = setup_text("", "font/o_drift.ttf", 35);
    sfIntRect rect = create_rect(0, 0, 399, 396);
    setup_button_texture(&upgrade.close, &rect, "img/close.png");
    setup_button_sounds(&upgrade.close, "sounds/click.ogg",
        "sounds/hover.ogg", env);
    return (upgrade);
}

void upgrade_display(SFWIN win, upgrade_menu_t menu, env_t *env)
{
    sfRenderWindow_drawSprite(win, menu.back.sprite, NULL);
    if (menu.upgrading->upgrade_1 != NULL) {
        sfRenderWindow_drawSprite(win, menu.upgrading->upgrade_1->sprite, NULL);
        sfRenderWindow_drawText(win, menu.cost_energy_1.text, NULL);
        sfRenderWindow_drawText(win, menu.cost_steel_1.text, NULL);
        sfRenderWindow_drawText(win, menu.name_1.text, NULL);
        sfRenderWindow_drawSprite(win, menu.icon_energy_1.sprite, NULL);
        sfRenderWindow_drawSprite(win, menu.icon_steel_1.sprite, NULL);
    }
    if (menu.upgrading->upgrade_2 != NULL) {
        sfRenderWindow_drawText(win, menu.cost_energy_2.text, NULL);
        sfRenderWindow_drawText(win, menu.cost_steel_2.text, NULL);
        sfRenderWindow_drawText(win, menu.name_2.text, NULL);
        sfRenderWindow_drawSprite(win, menu.upgrading->upgrade_2->sprite, NULL);
        sfRenderWindow_drawSprite(win, menu.icon_energy_2.sprite, NULL);
        sfRenderWindow_drawSprite(win, menu.icon_steel_2.sprite, NULL);
    }
    display_colored_upgrades(win, menu);
    display_button(win, &menu.close, env->keys);
}

void upgrade_destroy(upgrade_menu_t menu)
{
    destroy_button(menu.close);
    destroy_object(menu.back);
}
