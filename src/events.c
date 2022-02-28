/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** events.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"

void evolve_mouse(int *keys)
{
    if (keys[leftMouse] == press || keys[leftMouse] == release)
        keys[leftMouse] = (keys[leftMouse] + 1) % 4;
    if (keys[rightMouse] == press || keys[rightMouse] == release)
        keys[rightMouse] = (keys[rightMouse] + 1) % 4;
}

void print_events(int *keys)
{
    for (int i = 0; i < sfKeyCount + 2; i++)
        printf("%d", keys[i]);
    printf("\n");
}

int *get_events(sfRenderWindow *window, int *keys)
{
    sfEvent event;

    evolve_mouse(keys);
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        for (int i = 0; i < sfKeyCount; i++)
            keys[i] = sfKeyboard_isKeyPressed(i) == sfTrue;
        if (evntMousePressed && event.mouseButton.button == sfMouseLeft)
            keys[leftMouse] = press;
        if (evntMouseReleased && event.mouseButton.button == sfMouseLeft)
            keys[leftMouse] = release;
        if (evntMousePressed && event.mouseButton.button == sfMouseRight)
            keys[rightMouse] = press;
        if (evntMouseReleased && event.mouseButton.button == sfMouseRight)
            keys[rightMouse] = release;
    }
    return keys;
}
