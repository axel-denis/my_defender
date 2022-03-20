/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** main.c
*/

#include "menu.h"
#include "csfml.h"
#include "events.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "env.h"

int main(void)
{
    object mouse = setup_mouse("img/cursor.png", VC{1.7, 1.7});
    env_t *env = create_env();
    env->keys = init_keys();
    sfRenderWindow *window = create_windows(env);

    srand(get_true_mouse_pos(window).x * get_true_mouse_pos(window).y);
    main_menu(window, mouse, env);
    sfMusic_destroy(env->data.music);
    destroy_object(mouse);
    return (0);
}
