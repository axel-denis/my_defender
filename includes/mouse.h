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

object setup_button(char *, sfVector2f);
void update_mouse_cursor(sfRenderWindow *, object);

#endif /* !MOUSE_H_ */
