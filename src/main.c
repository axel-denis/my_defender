/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** main.c
*/

#include "csfml.h"
#include "structs.h"

button create_button(sfVector2f size, sfVector2f position)
{
    button bouton;

    bouton.is_clicked = sfFalse;
    bouton.is_hovered = sfFalse;
    bouton.position = position;
    bouton.size = size;
    bouton.sprite = sfSprite_create();
    return (bouton);
}

int main(int ac, char **av)
{
    sfRenderWindow *window;
    sfVideoMode main_w = {1920, 1080, 64};
    window = sfRenderWindow_create(main_w, "My defender", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    object background;
    background.sprite = sfSprite_create();
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_display(window);
    }
    return (0);
}
