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
