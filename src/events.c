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

int *init_keys(void)
{
    int *keys = malloc(sizeof(int) * (sfKeyCount + 2));

    for (int i = 0; i < sfKeyCount + 2; i++)
        keys[i] = 0;
    return keys;
}

void evolve_mouse(int *keys)
{
    if (keys[leftMouse] == press || keys[leftMouse] == release)
        keys[leftMouse] = (keys[leftMouse] + 1) % 4;
    if (keys[rightMouse] == press || keys[rightMouse] == release)
        keys[rightMouse] = (keys[rightMouse] + 1) % 4;
}

void evolve_keys(int *keys)
{
    for (int i = 0; i < sfKeyCount; i++) {
        if (sfKeyboard_isKeyPressed(i) == sfTrue && keys[i] == 1)
            keys[i]++;
        if (sfKeyboard_isKeyPressed(i) == sfTrue && keys[i] == 0)
            keys[i]++;
        if (sfKeyboard_isKeyPressed(i) == sfFalse && keys[i] == 3)
            keys[i] = 0;
        if (sfKeyboard_isKeyPressed(i) == sfFalse && keys[i] > 0 && keys[i] < 3)
            keys[i] = 3;
    }
}

/*
void print_events(int *keys)
{
    for (int i = 0; i < sfKeyCount + 2; i++)
        printf("%d", keys[i]);
    printf("\n");
}
*/

int *get_events(sfRenderWindow *window, int *keys)
{
    sfEvent event;
    sfVector2u window_size = sfRenderWindow_getSize(window);

    if (window_size.x < 800)
        sfRenderWindow_setSize(window, (sfVector2u){800, window_size.y});
    if (window_size.y < 600)
        sfRenderWindow_setSize(window, (sfVector2u){window_size.x, 600});
     if (window_size.x > 1920)
        sfRenderWindow_setSize(window, (sfVector2u){1920, window_size.y});
    if (window_size.y < 1080)
        sfRenderWindow_setSize(window, (sfVector2u){window_size.x, 1080});
    evolve_mouse(keys);
    evolve_keys(keys);
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
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
