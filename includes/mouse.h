/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** mouse
*/

#ifndef MOUSE_H_
    #define MOUSE_H_

    #include "csfml.h"
    #include "structs.h"
    #define leftMouse 101
    #define rightMouse 102
    #define press 1
    #define hold 2
    #define release 3
    #define evntMousePressed event.type == sfEvtMouseButtonPressed
    #define evntMouseReleased event.type == sfEvtMouseButtonReleased
    #define RELEASED (keys[leftMouse] == 0 || keys[leftMouse] == 3)
    #define CLICKED (keys[leftMouse] == 1 || keys[leftMouse] == 2)

object setup_mouse(char *, sfVector2f);
void update_mouse_cursor(sfRenderWindow *window, object mouse, sfClock *clock);
sfVector2f get_true_mouse_pos(sfRenderWindow *);

#endif /* !MOUSE_H_ */
