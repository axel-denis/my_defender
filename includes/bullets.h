/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** bullets
*/

#ifndef BULLETS_H
    #define BULLETS_H

    #include "csfml.h"
    #include "structs.h"
    #include "map.h"
    #include "maths.h"
    #define DIST_COLLISION 15

void free_bullet(bullet_t **bullet);
int evolve_bullet(bullet_t *bullet, env_t *env);
void evolve_display_bullets(env_t *env, sfRenderWindow *win);
bullet_t *create_bullet(enemy *target, turret_t *shooter);
bullet_t *null_bullet(void);
void new_bullet(env_t *env, enemy *target, turret_t *shooter);
int bullet_collision(bullet_t *bullet, env_t *env);

#endif
