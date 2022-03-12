/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ui
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "turrets.h"
#include "ui.h"

pop_button *create_turret_button_ui(void)
{
    pop_button *button = NULL;
    turret_t *turrets = create_turret_type();
    sfVector2f scale;
    sfVector2f pos;
    int i = 0;

    for (i = 0; turrets[i].type != 0; i++);
    button = malloc(sizeof(pop_button) * (i + 1));
    for (i = 0; turrets[i].type != 0; i++) {
        button[i].titre = setup_text(turrets[i].name, "font/Xero.ttf", 17);
        pos = VC{i * 180, 820};
        button[i].onglet = create_object("img/onglet.png", pos, VC{2, 2});
        pos = VC{i * 180 + 90, 900};
        scale = VC{.2, .2};
        button[i].icon = create_textured_object(turrets[i].texture, pos, scale);
        button[i].type = &(turrets[i]);
        sfText_setPosition(button[i].titre.text, VC{i * 180 + 12, 840});
        sfSprite_setOrigin(button[i].icon.sprite, VC{150, 250});
        sfSprite_setRotation(button[i].icon.sprite, 90);
    }
    button[i].onglet.sprite = NULL;
    return button;
}

void display_turret_icon(pop_button *buttons, sfRenderWindow *window, int i, sfVector2f mouse_pos)
{
    if (pos_in_square(mouse_pos, sfSprite_getGlobalBounds(buttons[i].icon.sprite))) {
        sfSprite_setColor(buttons[i].icon.sprite, sfColor_fromRGBA(220, 220, 220, 150));
        sfRenderWindow_drawSprite(window, buttons[i].icon.sprite, NULL);
        sfSprite_setColor(buttons[i].icon.sprite, sfColor_fromRGBA(255, 255, 255, 255));
    } else {
        sfRenderWindow_drawSprite(window, buttons[i].icon.sprite, NULL);
    }
}

void display_turrets_button_ui(pop_button *buttons, sfRenderWindow *window, int pickedup)
{
    sfVector2f mouse_pos = get_true_mouse_pos(window);
    sfFloatRect rect;

    for (int i = 0; buttons[i].onglet.sprite != NULL; i++) {
        rect = sfSprite_getGlobalBounds(buttons[i].onglet.sprite);
        if (pos_in_square(mouse_pos, rect) == sfTrue && sfSprite_getPosition(buttons[i].onglet.sprite).y > 800) {
            sfSprite_move(buttons[i].onglet.sprite, VC{0, -1});
            sfSprite_move(buttons[i].icon.sprite, VC{0, -1});
            sfText_move(buttons[i].titre.text, VC{0, -1});
        }
        if (pos_in_square(mouse_pos, rect) == sfFalse && sfSprite_getPosition(buttons[i].onglet.sprite).y < 820) {
            sfSprite_move(buttons[i].onglet.sprite, VC{0, 1});
            sfSprite_move(buttons[i].icon.sprite, VC{0, 1});
            sfText_move(buttons[i].titre.text, VC{0, 1});
        }
        sfRenderWindow_drawSprite(window, buttons[i].onglet.sprite, NULL);
        sfRenderWindow_drawText(window, buttons[i].titre.text, NULL);
        if (pickedup != i)
            display_turret_icon(buttons, window, i, mouse_pos);
    }
}

int pickup_turrets(pop_button *but, sfVector2f mouse_pos, int pick, int *keys, env_t *env)
{
    if (pick == -1) {
        for (int i = 0; but[i].onglet.sprite != NULL; i++) {
            sfFloatRect rect = sfSprite_getGlobalBounds(but[i].icon.sprite);

            if (pos_in_square(mouse_pos, rect) && keys[leftMouse] == 1) {
                sfSprite_setPosition(but[i].icon.sprite, mouse_pos);
                return i;
            }
        }
    } else {
        sfVector2i coo = get_case_coords(mouse_pos);

        if (keys[leftMouse] == 2 || keys[leftMouse] == 1) {
            if (coo.x > 0 && coo.y > 0 && coo.x < 32 && coo.y < 18 && env->c_game.map[coo.y][coo.x].type == 0)
                sfSprite_setPosition(but[pick].icon.sprite, VC{coo.x * 60 + 30, coo.y * 60 + 30});
            else
                sfSprite_setPosition(but[pick].icon.sprite, mouse_pos);
            return pick;
        }
        if (keys[leftMouse] == 3 || keys[leftMouse] == 0) {
            if (coo.x < 32 && coo.y < 18 && env->c_game.map[coo.y][coo.x].type == 0) {
                clone_turret(env, but[pick].type, VC{coo.x, coo.y});
                env->c_game.map[coo.y][coo.x].type = 3;
            }
            sfSprite_setPosition(but[pick].icon.sprite, VC{pick * 180 + 90, sfSprite_getPosition(but[pick].onglet.sprite).y + 80});
            return -1;
        }
    }
    return -1;
}

void display_picked_turret(int pickedup, pop_button *buttons, sfRenderWindow *w)
{
    if (pickedup != -1) {
        sfColor darken = sfColor_fromRGBA(220, 220, 220, 150);
        sfColor normal = sfColor_fromRGBA(255, 255, 255, 255);

        sfSprite_setColor(buttons[pickedup].icon.sprite, darken);
        sfRenderWindow_drawSprite(w, buttons[pickedup].icon.sprite, NULL);
        sfSprite_setColor(buttons[pickedup].icon.sprite, normal);
    }
}
