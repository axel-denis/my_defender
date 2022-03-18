/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** turrets_display c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"
#include "maths.h"

void d_range(sfVector2f mo, turret_t *ac, sfRenderWindow *win, sfCircleShape *r)
{
    sfVector2f pos = sfSprite_getPosition(ac->sprite);

    if (pos_in_square(mo, (sfFloatRect){pos.x - 30, pos.y - 30, 60, 60})) {
        sfCircleShape_setRadius(r, ac->range);
        sfCircleShape_setOrigin(r, VC{ac->range, ac->range});
        sfCircleShape_setPosition(r, VC{pos.x, pos.y});
        sfRenderWindow_drawCircleShape(win, r, NULL);
    }
}

void turret_action(turret_t *turret, env_t *env)
{
    enemy *nearest = NULL;
    sfVector2f near_pos = {0, 1};

    nearest = get_oldest(env, turret);
    if (nearest != NULL) {
        near_pos = sfSprite_getPosition(nearest->sprite);
        sfSprite_setRotation(turret->sprite,
        A_regarde_B(sfSprite_getPosition(turret->sprite), near_pos));
    }
    if (sfTime_asMilliseconds(sfClock_getElapsedTime(env->tempo))
        - turret->cooldown >= turret->damage_speed * 10) {
        new_bullet(env, nearest, turret);
        turret->cooldown =
            sfTime_asMilliseconds(sfClock_getElapsedTime(env->tempo));
    }
}

void display_turret(SFWIN win, env_t *env, sfCircleShape *range, sfVector2f mo)
{
    turret_t *actu = env->c_game.turrets;

    while (actu != NULL) {
        if (actu->type == 0) {
            actu = actu->next;
            continue;
        }
        turret_action(actu, env);
        d_range(mo, actu, win, range);
        sfRenderWindow_drawSprite(win, actu->sprite, NULL);
        actu = actu->next;
    }
}
