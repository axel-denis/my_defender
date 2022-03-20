/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** env.h
*/

#ifndef ENV_H
    #define ENV_H
    #include "structs.h"

env_t *create_env(void);
void create_base_game_data(env_t *env, game_data_t *game_data);
int game_clock_gestion(env_t *env, SFWIN window, object mouse);

#endif
