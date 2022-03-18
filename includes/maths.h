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

float dist_two_points(sfVector2f point1, sfVector2f point2);
float A_regarde_B(sfVector2f A, sfVector2f B);

#endif
