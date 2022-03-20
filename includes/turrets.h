/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** turrets.h
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"

#ifndef TURRET_H
    #define TURRET_H
    #define GEN_TURR ((turret->type > 10) * -1)

turret_t *create_null_turret(void);
turret_t *template_turret(int type, int dpa, int dmg_spd);
void clone_turret(env_t *env, turret_t *turret, sfVector2f pos);
void display_turret(sfRenderWindow *window, env_t *env,
sfCircleShape *range, sfVector2f mouse_pos);
turret_t create_turret_from_file(env_t *env, char *titre);
turret_t *create_turret_type(env_t *env);
turret_t create_turret_from_file(env_t *env, char *titre);
turret_t *create_malloc_turret_from_file(env_t *env, char *titre);
void upgrade_turret(turret_t *prec_turret, int upgrade, env_t *env);
turret_t *find_turret_by_pos(env_t *env, sfVector2f pos);
void set_turret_origin_and_cost(turret_t *actual, env_t *env);
#endif
