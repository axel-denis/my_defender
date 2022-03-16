/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ui_display2 c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "turrets.h"
#include "hud.h"
#include "ui.h"

void display_turret_icon(pop_button *but, sfRenderWindow *win, int i)
{
    sfColor dark = sfColor_fromRGBA(220, 220, 220, 150);
    sfVector2f p = get_true_mouse_pos(win);

    if (pos_in_square(p, sfSprite_getGlobalBounds(but[i].icon.sprite))) {
        sfSprite_setColor(but[i].icon.sprite, dark);
        sfRenderWindow_drawSprite(win, but[i].icon.sprite, NULL);
        sfSprite_setColor(but[i].icon.sprite, sfWhite);
    } else {
        sfRenderWindow_drawSprite(win, but[i].icon.sprite, NULL);
    }
}

void display_picked_turret(int pickedup, pop_button *but, sfRenderWindow *win)
{
    if (pickedup != -1) {
        sfColor darken = sfColor_fromRGBA(220, 220, 220, 150);
        sfColor normal = sfColor_fromRGBA(255, 255, 255, 255);

        sfSprite_setColor(but[pickedup].icon.sprite, darken);
        sfRenderWindow_drawSprite(win, but[pickedup].icon.sprite, NULL);
        sfSprite_setColor(but[pickedup].icon.sprite, normal);
    }
}
