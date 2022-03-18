/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** range.c
*/

#include "csfml.h"

sfCircleShape *create_range()
{
    sfCircleShape *range = sfCircleShape_create();

    sfCircleShape_setOutlineColor(range, sfColor_fromRGBA(200, 200, 200, 200));
    sfCircleShape_setOutlineThickness(range, 5);
    sfCircleShape_setFillColor(range, sfColor_fromRGBA(200, 200, 200, 50));
    sfCircleShape_setPosition(range, VC{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
    sfCircleShape_setRadius(range, WINDOW_HEIGHT / 2);
    sfCircleShape_setOrigin(range, VC{WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2});
    return (range);
}
