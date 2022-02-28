/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** main.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"

int get_events(sfRenderWindow *window)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
            return (0);
    }
    return (1);
}

int main(int ac, char **av)
{
    sfRenderWindow *window;
    int close = 1;
    sfVideoMode main_w = {1920, 1080, 64};
    object background;
    button button = create_button(VC{0.2, 0.2}, VC{1920 / 2, 1080 / 2}, sfTrue);
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    window = sfRenderWindow_create(main_w, "My defender", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    object mouse = setup_button("img/cursor.png", VC{0.05, 0.05});
    setup_button_texture(&button, &square, "img/Blue_button.png");
    setup_button_text(&button, "Resume", "font/Absolute-Xero.ttf", 40);
    while (sfRenderWindow_isOpen(window) && close == 1) {
        sfRenderWindow_clear(window, sfBlack);
        display_button(window, button);
        update_mouse_cursor(window, mouse);
        close = get_events(window);
        sfRenderWindow_display(window);
    }
    return (0);
}
