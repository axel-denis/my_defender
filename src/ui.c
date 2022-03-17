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

int detect_what_pickup(pop_button *but, sfVector2f mouse_pos, int *keys)
{
    sfFloatRect rect;

    for (int i = 0; but[i].onglet.sprite != NULL; i++) {
        rect = sfSprite_getGlobalBounds(but[i].icon.sprite);
        if (pos_in_square(mouse_pos, rect) && keys[leftMouse] == 1) {
            sfSprite_setPosition(but[i].icon.sprite, mouse_pos);
            return i;
        }
    }
    return -1;
}

int hold_the_turret(pop_button *but, sfVector2f mouse_pos, int pick, env_t *env)
{
    sfVector2i co = get_case_coords(mouse_pos);

    if (env->keys[leftMouse] == 2 || env->keys[leftMouse] == 1) {
        if (co.x >= 0 && co.y >= 0 && co.x < 32 && co.y < 18
            && env->c_game.map[co.y][co.x].type == 0)
            sfSprite_setPosition(but[pick].icon.sprite,
                VC{co.x * 60 + 30, co.y * 60 + 30});
        else
            sfSprite_setPosition(but[pick].icon.sprite, mouse_pos);
        return pick;
    }
    return (-1);
}

int pick_the_turret(pop_button *but, sfVector2f mouse_pos, int pick, env_t *env)
{
    sfVector2i co = get_case_coords(mouse_pos);
    int returned = hold_the_turret(but, mouse_pos, pick, env);

    if (env->keys[leftMouse] == 3 || env->keys[leftMouse] == 0) {
        if (co.x < 32 && co.y < 18 && env->c_game.map[co.y][co.x].type == 0
            && env->c_game.player_stats.energy > but[pick].type->energy_cost
            && env->c_game.player_stats.steel > but[pick].type->steel_cost) {
            clone_turret(env, but[pick].type, VC{co.x, co.y});
            env->c_game.player_stats.energy -= but[pick].type->energy_cost;
            env->c_game.player_stats.steel -= but[pick].type->steel_cost;
            env->c_game.map[co.y][co.x].type = 3;
        }
        sfSprite_setPosition(but[pick].icon.sprite, VC{pick * 180 + 90,
        sfSprite_getPosition(but[pick].onglet.sprite).y + 80});
    }
    return (returned);
}

int pickup_turrets(pop_button *but, sfVector2f mouse_pos, int pick, env_t *env)
{
    if (pick == -1) {
        return (detect_what_pickup(but, mouse_pos, env->keys));
    } else {
        return (pick_the_turret(but, mouse_pos, pick, env));
    }
    return -1;
}
