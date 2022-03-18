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

void display_turret(sfRenderWindow *w, env_t *e, sfCircleShape *r, sfVector2f m)
{
    turret_t *actu = e->c_game.turrets;
    enemy *nearest = NULL;
    sfVector2f near_pos = {0, 1};

    while (actu != NULL) {
        if (actu->type == 0) {
            actu = actu->next;
            continue;
        }
        nearest = get_oldest(e, actu);
        if (nearest != NULL) {
            near_pos = sfSprite_getPosition(nearest->sprite);
            sfSprite_setRotation(actu->sprite,
            A_regarde_B(sfSprite_getPosition(actu->sprite), near_pos));
        }
        d_range(m, actu, w, r);
        new_bullet(e, nearest, actu);
        sfRenderWindow_drawSprite(w, actu->sprite, NULL);
        actu = actu->next;
    }
}
