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
#include "bullets.h"
#include "map.h"
#include "maths.h"
#include "turrets.h"

void d_range(sfVector2f mouse, turret_t *actua, SFWIN win, sfCircleShape *range)
{
    sfVector2f pos = sfSprite_getPosition(actua->sprite);

    if (pos_in_square(mouse, (sfFloatRect){pos.x - 30, pos.y - 30, 60, 60})) {
        sfCircleShape_setRadius(range, actua->range);
        sfCircleShape_setOrigin(range, VC{actua->range, actua->range});
        sfCircleShape_setPosition(range, VC{pos.x, pos.y});
        sfRenderWindow_drawCircleShape(win, range, NULL);
    }
}

void turret_consume(turret_t *turret, env_t *env, enemy *nearest)
{
    if (nearest != NULL && turret->type <= 10) {
        env->c_game.player_stats.steel -= turret->steel_per_s;
        env->c_game.player_stats.energy -= turret->energy_per_s;
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
        if (turret->type <= 10)
            new_bullet(env, nearest, turret);
        turret->cooldown =
            sfTime_asMilliseconds(sfClock_getElapsedTime(env->tempo));
        turret_consume(turret, env, nearest);
    }
}

void display_turret(SFWIN win, env_t *env, sfCircleShape *range, sfVector2f mou)
{
    turret_t *actu = env->c_game.turrets;

    while (actu != NULL) {
        if (actu->type == 0) {
            actu = actu->next;
            continue;
        }
        turret_action(actu, env);
        d_range(mou, actu, win, range);
        sfRenderWindow_drawSprite(win, actu->sprite, NULL);
        actu = actu->next;
    }
}
