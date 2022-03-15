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

void display_turret_icon(pop_button *bu, sfRenderWindow *w, int i)
{
    sfColor dark = sfColor_fromRGBA(220, 220, 220, 150);
    sfVector2f p = get_true_mouse_pos(w);

    if (pos_in_square(p, sfSprite_getGlobalBounds(bu[i].icon.sprite))) {
        sfSprite_setColor(bu[i].icon.sprite, dark);
        sfRenderWindow_drawSprite(w, bu[i].icon.sprite, NULL);
        sfSprite_setColor(bu[i].icon.sprite, sfWhite);
    } else {
        sfRenderWindow_drawSprite(w, bu[i].icon.sprite, NULL);
    }
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
