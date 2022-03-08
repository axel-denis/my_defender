/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** enemy
*/

#ifndef ENEMY_H_
    #define ENEMY_H_

void create_enemy_type_1(env_t *env);
void evolve_enemy(env_t *env, enemy *mob);
void display_enemies(sfRenderWindow *window, env_t *env);
void evolve_all_enemies(env_t *env);
void create_test_enemy(env_t *env, int health);
enemy *remove_next_enemy_if_needed(enemy *precedent);

#endif /* !ENEMY_H_ */
