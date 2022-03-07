/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** math_utils
*/

#include "csfml.h"
#include <math.h>

float distance_entre_deux_points(sfVector2f point1, sfVector2f point2)
{
    return (sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2)));
}
