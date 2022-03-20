/*
** EPITECH PROJECT, 2022
** My_defender
** File description:
** scoreboard
*/

#include "csfml.h"
#include "lib.h"
#include "menu.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"
//515
//50
scoreboard_t scoreboard_create(void)
{
    scoreboard_t score;

    score.back = create_object("img/panel.png", VC{50, 175}, VC{0.5, 2});
    sfSprite_rotate(score.back.sprite, 90);
    score.title = setup_text("Scoreboard", "font/Xero.ttf", 40);
    sfText_setPosition(score.title.text, VC{-445, 225});
    return (score);
}

void scoreboard_display(SFWIN window, scoreboard_t score)
{
    if (pos_in_square(get_true_mouse_pos(window),
    sfSprite_getGlobalBounds(score.back.sprite))
    && sfSprite_getPosition(score.back.sprite).x < 515) {
        sfSprite_move(score.back.sprite, VC{5, 0});
        sfText_move(score.title.text, VC{5, 0});
    }
    if (pos_in_square(get_true_mouse_pos(window),
    sfSprite_getGlobalBounds(score.back.sprite)) == sfFalse
    && sfSprite_getPosition(score.back.sprite).x > 50) {
        sfSprite_move(score.back.sprite, VC{-5, 0});
        sfText_move(score.title.text, VC{-5, 0});
    }
    sfRenderWindow_drawSprite(window, score.back.sprite, NULL);
    sfRenderWindow_drawText(window, score.title.text, NULL);
}
