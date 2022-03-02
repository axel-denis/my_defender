/*
** EPITECH PROJECT, 2021
** myscreensaver
** File description:
** csfml.h
*/

#ifndef CSFML_INCLUDES
    #define CSFML_INCLUDES
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <stdarg.h>
    #include <string.h>
    #include <unistd.h>
    #include <math.h>

    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>

    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080

    #include "structs.h"

sfIntRect create_rect(int, int, int, int);
sfVector2f itofv2(sfVector2i);
sfBool pos_in_square(sfVector2f, sfFloatRect);
void destroy_object(object);
text setup_text(char *, char *, int);
object create_object(char *file, sfVector2f pos, sfVector2f scale);

#endif
