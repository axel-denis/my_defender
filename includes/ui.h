/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ui
*/

#ifndef UI_H_
    #define UI_H_

    #define NOT_HOVER pos_in_square(mouse_pos, rect) == sfFalse
    #define HOVER pos_in_square(mouse_pos, rect) == sfTrue

pop_button *create_turret_button_ui(env_t *env);
void display_turret_icon(pop_button *buttons, sfRenderWindow *window, int i);
void display_turret_button_ui(pop_button *, sfRenderWindow *, int , env_t *env);
int pickup_turrets(pop_button *but, sfVector2f mouse_pos, int pick, env_t *env);
void display_picked_turret(int pickedup, pop_button *butt, sfRenderWindow *win);
void display_turret_icon(pop_button *bu, sfRenderWindow *window, int i);
void display_picked_turret(int pickedup, pop_button *buttons, sfRenderWindow *);
void upgrade_menu(env_t *env, sfRenderWindow *window, upgrade_menu_t *, int);
upgrade_menu_t upgrade_create(env_t *env);

#endif
