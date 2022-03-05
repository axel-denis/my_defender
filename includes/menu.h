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

void main_menu(sfRenderWindow *, object, int *, env_t *);
void game(sfRenderWindow *window, object mouse, int *keys, env_t *env);
void options(sfRenderWindow *window, object mouse, int *keys, env_t *env);

#endif /* !MENU_H_ */
