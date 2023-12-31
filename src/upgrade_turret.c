/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** upgrade_turret.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "turrets.h"
#include "hud.h"
#include "ui.h"
#include "button.h"
#include "maths.h"

void execute_upgrade(env_t *env, sfVector2f pos, upgrade_menu_t *menu)
{
    if (env->keys[leftMouse] == 3 && pos_in_square(pos,
        sfSprite_getGlobalBounds(menu->close.sprite)) == sfTrue)
        menu->upgrading = NULL;
    if (menu->upgrading != NULL && UPGT->upgrade_1 != NULL &&
        pos_in_square(pos,
        sfSprite_getGlobalBounds(UPGT->upgrade_1->sprite))
        == sfTrue && env->keys[leftMouse] == 3
        && UPGT->upgrade_1->energy_cost <= env->c_game.player_stats.energy
        && UPGT->upgrade_1->steel_cost <= env->c_game.player_stats.steel) {
        upgrade_turret(UPGT, 1, env);
        UPGT = NULL;
    } else if (UPGT != NULL && UPGT->upgrade_2 != NULL &&
        pos_in_square(pos,
        sfSprite_getGlobalBounds(UPGT->upgrade_2->sprite))
        == sfTrue && env->keys[leftMouse] == 3
        && UPGT->upgrade_2->energy_cost <= env->c_game.player_stats.energy
        && UPGT->upgrade_2->steel_cost <= env->c_game.player_stats.steel) {
        upgrade_turret(UPGT, 2, env);
        UPGT = NULL;
    }
}

void copy_turret(turret_t *turret, turret_t *template)
{
    turret->damage_per_action = template->damage_per_action;
    turret->damage_speed = template->damage_speed;
    turret->energy_cost = template->energy_cost;
    turret->energy_per_s = template->energy_per_s;
    turret->is_base = template->is_base;
    turret->name = template->name;
    turret->range = template->range;
    turret->texture = template->texture;
    turret->sprite = sfSprite_create();
    sfSprite_setTexture(turret->sprite, turret->texture, sfTrue);
    turret->steel_cost = template->steel_cost;
    turret->steel_per_s = template->steel_per_s;
    turret->type = template->type;
    turret->upgrade_1 = template->upgrade_1;
    turret->upgrade_2 = template->upgrade_2;
}

void apply_upgrade_cost(env_t *env, turret_t *turret, int upgrade)
{
    if (upgrade == 1) {
        env->c_game.player_stats.steel -= turret->upgrade_1->steel_cost;
        env->c_game.player_stats.energy -= turret->upgrade_1->energy_cost;
    } else {
        env->c_game.player_stats.steel -= turret->upgrade_2->steel_cost;
        env->c_game.player_stats.energy -= turret->upgrade_2->energy_cost;
    }
}

void upgrade_turret(turret_t *turret, int upgrade, env_t *env)
{
    sfVector2f pos;

    if (turret != NULL) {
        if (turret->upgrade_1 == NULL && upgrade == 1)
            return;
        if (turret->upgrade_2 == NULL && upgrade > 1)
            return;
    } else {
        return;
    }
    pos = sfSprite_getPosition(turret->sprite);
    apply_upgrade_cost(env, turret, upgrade);
    if (upgrade == 1)
        copy_turret(turret, turret->upgrade_1);
    else
        copy_turret(turret, turret->upgrade_2);
    set_turret_origin_and_cost(turret, env);
    sfSprite_setScale(turret->sprite, VC{.9, .9});
    sfSprite_setPosition(turret->sprite, pos);
}

turret_t *find_turret_by_pos(env_t *env, sfVector2f pos)
{
    turret_t *actual = env->c_game.turrets;
    turret_t *output = NULL;
    int act_dist;
    int dist = 2000;

    while (actual != NULL) {
        if (actual->type == 0) {
            actual = actual->next;
            continue;
        }
        act_dist = dist_two_points(sfSprite_getPosition(actual->sprite), pos);
        if (act_dist < dist) {
            dist = act_dist;
            output = actual;
        }
        actual = actual->next;
    }
    return output;
}
