/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** main.c
*/

#include "error_handling.h"
#include "menu.h"
#include "enemy.h"
#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"
#include "maths.h"
#include "map.h"
#include "hud.h"
#include "turrets.h"
#include "ui.h"
#include "bullets.h"
#include "env.h"
#include "range.h"

int main(void)
{
    object mouse = setup_mouse("img/cursor.png", VC{1.7, 1.7});
    env_t *env = create_env();
    env->keys = init_keys();
    sfRenderWindow *window = create_windows(env);

    main_menu(window, mouse, env);
    sfMusic_destroy(env->data.music);
    destroy_object(mouse);
    return (0);
}
