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

void main_menu(sfRenderWindow *, object, env_t *);
void options(sfRenderWindow *window, object mouse, int *keys, env_t *env);
void options(sfRenderWindow *window, object mouse, int *keys, env_t *env);
button *create_buttons_options(env_t *env);
void setup_buttons_options(button *buttons, env_t *env);
void volume_manager(button *but, sfRenderWindow *window, int *keys, env_t *env);
void volume_manager2(button *but, sfRenderWindow *window, int *keys, env_t *);
void fps_manager(button *but, sfRenderWindow *window, int *keys, env_t *env);
int pause_menu(sfRenderWindow *window, object mouse, env_t *env);
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
int create_game(env_t *env);
void lose_menu(sfRenderWindow *window, object mouse, int *keys, env_t *env);
char *set_screen_txt(env_t *env);
void game(sfRenderWindow *, object, env_t *, game_data_t *);
void launch_game(sfRenderWindow *, object, env_t *);
void how_to_menu(sfRenderWindow *window, object mouse, env_t *env);
void scoreboard_display(SFWIN window, scoreboard_t score);
scoreboard_t scoreboard_create(env_t *env);
void free_lose_menu(text texte, text score, button *buttons);
void write_score_in_scoreboard(env_t *env);
char **scores_to_array(void);

#endif
