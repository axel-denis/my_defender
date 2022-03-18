/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** enemy
*/

#ifndef ENEMY_H_
    #define ENEMY_H_

    #include "structs.h"

enemy *create_null_enemy(void);
void evolve_enemy(env_t *env, enemy *mob);
void display_enemies(sfRenderWindow *window, env_t *env);
void evolve_all_enemies(env_t *env);
enemy *create_enemies_type(void);
enemy *remove_next_enemy_if_needed(enemy *precedent);
enemy *get_oldest(env_t *env, turret_t *turret);
wave_t wave_create(env_t *env, enemy *enemies_type);
void clone_enemy(env_t *env, enemy to_clone);
wave_t wave_manage(env_t *env, enemy *enemies_type, wave_t current_wave);
enemy *last_e_link(enemy *first);
enemy create_enemy_from_file(char *titre);

#endif /* !ENEMY_H_ */
