/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** map_reader.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"
#include "map.h"

sfSprite *get_case_from_mouse(env_t *env, sfVector2f mouse_pos)
{
    sfVector2i case_pos = get_case_coords(mouse_pos);

    if (case_pos.y < 0 || case_pos.x < 0
        || case_pos.y >= 18 || case_pos.x >= 32)
        return NULL;
    return env->map[case_pos.y][case_pos.x].sprite;
}

sfVector2i get_case_coords(sfVector2f position)
{
    int x = (position.x / WINDOW_WIDTH) * 32;
    int y = (position.y / WINDOW_HEIGHT) * 18;

    return (sfVector2i) {x, y};
}

void setmap_opacity(env_t *env)
{
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            if (env->map[i][j].type == 0 || env->map[i][j].type == 3)
                sfSprite_setColor(env->map[i][j].sprite, sfColor_fromRGBA(255, 255, 255, 100));
            if (env->map[i][j].type == 1 || env->map[i][j].type == 2)
                sfSprite_setColor(env->map[i][j].sprite, sfColor_fromRGBA(255, 255, 255, 150));
        }
    }
}

void display_map(env_t *env, sfRenderWindow *window)
{
    sfColor old_color;

    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            if (get_case_from_mouse(env, get_true_mouse_pos(window)) == env->map[i][j].sprite) {
                old_color = sfSprite_getColor(env->map[i][j].sprite);
                sfSprite_setColor(env->map[i][j].sprite, sfColor_fromRGBA(255, 255, 255, 255));
                sfRenderWindow_drawSprite(window, env->map[i][j].sprite, NULL);
                sfSprite_setColor(env->map[i][j].sprite, old_color);
            } else
                sfRenderWindow_drawSprite(window, env->map[i][j].sprite, NULL);
        }
    }
}
