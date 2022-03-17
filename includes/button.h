/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** button
*/

#ifndef BUTTON_H_
    #define BUTTON_H_

    #include "csfml.h"
    #include "structs.h"

void setup_button_text(button *, char *, char *, int);
button create_button(sfVector2f, sfVector2f, sfBool);
void setup_button_texture(button *, sfIntRect *, char *);
void setup_button_sounds(button *bouton, char *click, char *hover, env_t *env);

void center_button_text(button *);
void display_button(sfRenderWindow *, button *, int *);
void destroy_button(button);
sfBool is_pressed(button, sfRenderWindow *, int *);

#endif /* !BUTTON_H_ */
