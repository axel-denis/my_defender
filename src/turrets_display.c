/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** turrets_display
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"
#include "maths.h"

void display_turrets(sfRenderWindow *window, env_t *env, sfCircleShape *range, sfVector2f mouse_pos)
{
    turret_t *actual = env->c_game.turrets;
    enemy *nearest = NULL;
    sfVector2f near_pos = {0, 1};
    sfVector2f pos = {0, 0};

    while (actual != NULL) {
        if (actual->type == 0) {
            actual = actual->next;
            continue;
        }
        nearest = get_nearest(env, sfSprite_getPosition(actual->sprite));
        pos = sfSprite_getPosition(actual->sprite);
        if (nearest != NULL) {
            near_pos = sfSprite_getPosition(nearest->sprite);
            sfSprite_setRotation(actual->sprite, A_regarde_B(pos, near_pos));
        }
        if (pos_in_square(mouse_pos, (sfFloatRect){pos.x - 30, pos.y - 30, 60, 60})) {
            sfCircleShape_setRadius(range, actual->range);
            sfCircleShape_setOrigin(range, VC{actual->range, actual->range});
            sfCircleShape_setPosition(range, VC{pos.x, pos.y});
            sfRenderWindow_drawCircleShape(window, range, NULL);
        }
        new_bullet(env, get_nearest(env, sfSprite_getPosition(actual->sprite)), actual);
        sfRenderWindow_drawSprite(window, actual->sprite, NULL);
        actual = actual->next;
    }
}
