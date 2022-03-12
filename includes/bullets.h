
#ifndef BULLETS_H
    #define BULLETS_H

    #include "csfml.h"
    #include "structs.h"
    #include "map.h"
    #include "maths.h"

void free_bullet(bullet_t **bullet);
int evolve_bullet(bullet_t *bullet);
void evolve_display_bullets(env_t *env, sfRenderWindow *win);
bullet_t *create_bullet(enemy *target, turret_t *shooter);
bullet_t *null_bullet(void);
void new_bullet(env_t *env, enemy *target, turret_t *shooter);

#endif
