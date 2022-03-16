/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** maths
*/

#ifndef MATHS_H_
    #define MATHS_H_

    #include <math.h>

    #define DToR(Angle) (Angle * M_PI / 180.0)
    #define RToD(Angle) (Angle * 180.0 / M_PI)
    #define MIN(x, y) (y < x) ? y : x
    #define ATOV(angle) cos(angle * 2 * M_PI / 360), sin(angle * 2 * M_PI / 360)

float dist_two_points(sfVector2f point1, sfVector2f point2);
float A_regarde_B(sfVector2f A, sfVector2f B);

#endif /* !MATHS_H_ */
