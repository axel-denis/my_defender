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
#include "events.h"

button *create_buttons_menu(void)
{
    button *buttons = malloc(sizeof(button) * 3);
    sfIntRect square = create_rect(0, 0, 6065 / 3, 833);

    buttons[0] = create_button(VC{0.2, 0.2}, VC{1920 / 2 - ((6065 / 3) / 2) * 0.2, 1080 / 2 - 200}, sfTrue);
    buttons[1] = create_button(VC{0.2, 0.2}, VC{1920 / 2 - ((6065 / 3) / 2) * 0.2, 1080 / 2}, sfTrue);
    buttons[2] = create_button(VC{0.2, 0.2}, VC{1920 / 2 - ((6065 / 3) / 2) * 0.2, 1080 / 2 + 200}, sfTrue);
    setup_button_texture(&(buttons[0]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[1]), &square, "img/Blue_button.png");
    setup_button_texture(&(buttons[2]), &square, "img/Blue_button.png");
    setup_button_text(&(buttons[0]), "Start", "font/Absolute-Xero.ttf", 40);
    setup_button_text(&(buttons[1]), "Options", "font/Absolute-Xero.ttf", 40);
    setup_button_text(&(buttons[2]), "Quit", "font/Absolute-Xero.ttf", 40);
    return (buttons);
}

void options(sfRenderWindow *window, object mouse, int *keys)
{
    int open = 1;

    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
    }
    keys[sfKeyEscape] = 0;
}

void game(sfRenderWindow *window, object mouse, int *keys)
{
    int open = 1;

    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
    }
    keys[sfKeyEscape] = 0;
}

void main_menu(sfRenderWindow *window, object mouse, int *keys)
{
    button *buttons = create_buttons_menu();
    int open = 1;
    text text = setup_text("my_defender", "font/oceanicdriftlaser.ttf", 30);

    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        for (int i = 0; i < 3; i++)
            display_button(window, buttons[i], keys);
        update_mouse_cursor(window, mouse);
        if (is_pressed(buttons[0], window, keys) == sfTrue)
            game(window, mouse, keys);
        if (is_pressed(buttons[1], window, keys) == sfTrue)
            options(window, mouse, keys);
        if (is_pressed(buttons[2], window, keys) == sfTrue)
            open = 0;
        sfRenderWindow_display(window);
    }
    for (int i = 0; i < 3; i++)
        destroy_button(buttons[i]);
}

int main(int ac, char **av)
{
    int *keys = init_keys();
    sfVideoMode main_w = {1920, 1080, 64};
    sfRenderWindow *window;
    object mouse = setup_mouse("img/cursor.png", VC{0.05, 0.05});

    window = sfRenderWindow_create(main_w, "My defender", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    main_menu(window, mouse, keys);
    destroy_object(mouse);
    return (0);
}
