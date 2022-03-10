/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Espace de travail)
** File description:
** menu
*/

#ifndef MENU_H_
    #define MENU_H_

    #include "csfml.h"
    #include "structs.h"

    #define ENGLISH (env->langue[0] == 'E')

void main_menu(sfRenderWindow *, object, int *, env_t *);
void game(sfRenderWindow *window, object mouse, int *keys, env_t *env);
void options(sfRenderWindow *window, object mouse, int *keys, env_t *env);
void options(sfRenderWindow *window, object mouse, int *keys, env_t *env);
button *create_buttons_options(env_t *env);
void setup_buttons_options(button *buttons, env_t *env);
void volume_manager(button *but, sfRenderWindow *window, int *keys, env_t *env);
void volume_manager2(button *but, sfRenderWindow *window, int *keys, env_t *);
void fps_manager(button *but, sfRenderWindow *window, int *keys, env_t *env);
int pause_menu(sfRenderWindow *window, object mouse, int *keys, env_t *env);
void display_background(sfRenderWindow *win, object fr, object en, env_t *env);
void vsync_manager(button *but, sfRenderWindow *window, int *keys, env_t *env);
void resolution_manager(button *but, sfRenderWindow *wind, int *keys, env_t *e);
void set_button_volume_txt(button *buttons, env_t *env);
void set_button_fps_txt(button *buttons, env_t *env);
void set_button_resolution_txt(button *buttons, env_t *env);
void set_button_vsync_txt(button *buttons, env_t *env);
void set_button_screen_txt(button *buttons, env_t *env);
void screen_manager(button *but, sfRenderWindow *window, int *keys, env_t *env);
void langue_manager(button *but, sfRenderWindow *window, int *keys, env_t *env);
char *set_screen_txt(env_t *env);

#endif /* !MENU_H_ */
