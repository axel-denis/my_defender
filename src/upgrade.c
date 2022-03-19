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
            sfText_setString(menu->name_1.text,
            menu->upgrading->upgrade_1->name);
            sfText_setString(menu->name_2.text,
            menu->upgrading->upgrade_2->name);
        }
        actual = actual->next;
    }
}

void upgrade_menu(env_t *env, SFWIN window, upgrade_menu_t *menu, int pick)
{
    if (menu->upgrading == NULL)
        upgrade_menu_open(env, window, menu, pick);
    else {
        if (env->keys[leftMouse] == 3 &&
            pos_in_square(get_true_mouse_pos(window),
            sfSprite_getGlobalBounds(menu->close.sprite)) == sfTrue)
            menu->upgrading = NULL;
    }
    return;
}

upgrade_menu_t upgrade_create(env_t *env)
{
    upgrade_menu_t upgrade;

    upgrade.upgrading = NULL;
    upgrade.back = create_object("img/onglet.png", VC{0, 900}, VC{21.31, 1.5});
    upgrade.close = create_button(VC{.1, .1}, VC{1850, 920}, sfFalse);
    upgrade.name_1 = setup_text("empty", "font/o_drift.ttf", 25);
    upgrade.name_2 = setup_text("empty", "font/o_drift.ttf", 25);
    sfIntRect rect = create_rect(0, 0, 399, 396);
    setup_button_texture(&upgrade.close, &rect, "img/close.png");
    setup_button_sounds(&upgrade.close, "sounds/click.ogg",
        "sounds/hover.ogg", env);
    return (upgrade);
}

void upgrade_display(SFWIN win, upgrade_menu_t menu, env_t *env)
{
    sfSprite_setScale(menu.upgrading->upgrade_1->sprite, VC{2, 2});
    sfSprite_setPosition(menu.upgrading->upgrade_1->sprite, VC{480, 955});
    sfSprite_setScale(menu.upgrading->upgrade_2->sprite, VC{2, 2});
    sfSprite_setPosition(menu.upgrading->upgrade_2->sprite, VC{1440 -
    sfSprite_getGlobalBounds(menu.upgrading->upgrade_2->sprite).width, 955});
    sfRenderWindow_drawText(win, menu.name_1.text, NULL);
    sfRenderWindow_drawText(win, menu.name_2.text, NULL);
    sfRenderWindow_drawSprite(win, menu.back.sprite, NULL);
    sfRenderWindow_drawSprite(win, menu.upgrading->upgrade_1->sprite, NULL);
    sfRenderWindow_drawSprite(win, menu.upgrading->upgrade_2->sprite, NULL);
    display_button(win, &menu.close, env->keys);
}

void upgrade_destroy(upgrade_menu_t menu)
{
    destroy_button(menu.close);
    destroy_object(menu.back);
}
