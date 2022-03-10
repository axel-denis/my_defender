/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** enemy_display.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"
#include "maths.h"

void display_enemies(sfRenderWindow *window, env_t *env)
{
    enemy *actual = env->c_game.enemies;

    while (actual != NULL) {
        if (actual->type != 0)
            sfRenderWindow_drawSprite(window, actual->sprite, NULL);
        actual = actual->next;
    }
}

void display_turrets(sfRenderWindow *window, env_t *env)
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
        printf("drawed\n");
        nearest = get_nearest(env, sfSprite_getPosition(actual->sprite));
        if (nearest != NULL) {
            near_pos = sfSprite_getPosition(nearest->sprite);
            sfSprite_setRotation(actual->sprite, A_regarde_B(pos, near_pos));
        }
        printf("(%f)\n", A_regarde_B(pos, near_pos));
/*         sfSprite *test = sfSprite_create();
        sfTexture *texture = sfTexture_createFromFile("img/turret1_1.png", NULL);
        sfSprite_setTexture(test, texture, sfFalse);
        sfSprite_setScale(test, sfSprite_getScale(actual->sprite));
        sfSprite_setTexture(actual->sprite, env->data.ground_texture, sfFalse);
        sfSprite_setScale(actual->sprite, VC{1,1});
        sfRenderWindow_drawSprite(window, test, NULL); */
        printf("x: %f y: %f scaleX:%f scaleY:%f\n", sfSprite_getPosition(actual->sprite).x, sfSprite_getPosition(actual->sprite).y, sfSprite_getScale(actual->sprite).x, sfSprite_getScale(actual->sprite).y);
        sfRenderWindow_drawSprite(window, actual->sprite, NULL);
        actual = actual->next;
    }
    printf("========\n");
}
