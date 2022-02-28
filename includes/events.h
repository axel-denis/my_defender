/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** events.h
*/

#ifndef EVENTS_H
    #define EVENTS_H

    #include "csfml.h"

    void evolve_mouse(int *keys);
    void print_events(int *keys);
    int *get_events(sfRenderWindow *window, int *keys);

#endif
