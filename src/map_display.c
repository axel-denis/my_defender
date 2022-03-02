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

    printf("%d %d\n", case_pos.x, case_pos.y);
    return env->map[case_pos.y][case_pos.x].sprite;
}

sfVector2i get_case_coords(sfVector2f position)
{
    int x = (position.x / 1920) * 32;
    int y = (position.y / 1080) * 18;

    return (sfVector2i) {x, y};
}

void display_map(env_t *env, sfRenderWindow *window)
{
    sfVector2f mouse = get_true_mouse_pos(window);

    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            sfSprite_setPosition(env->map[i][j].sprite, (sfVector2f) {j * 60, i * 60});
            sfRenderWindow_drawSprite(window, env->map[i][j].sprite, NULL);
        }
    }
}