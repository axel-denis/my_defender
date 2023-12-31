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

int size_of_scores(FILE *fd, char *buffer)
{
    size_t size = 0;
    int len = 0;

    for (int i = 0; getline(&buffer, &size, fd) != -1 && i < 14; i++)
        len += size + 8;
    fclose(fd);
    return (len);
}

char *create_score_from_file(char *titre)
{
    FILE *fd = fopen(titre, "r");
    char *buffer = NULL;
    char *scores;
    int len;
    size_t size = 0;

    if (fd == NULL)
        return NULL;
    len = size_of_scores(fd, buffer);
    scores = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i != len; i++)
        scores[i] = '\0';
    fd = fopen(titre, "r");
    for (int i = 0; getline(&buffer, &size, fd) != -1 && i < 14; i++)
        if (my_get_nbr(buffer) > 0) {
            scores = my_strcat(scores, "score : ");
            scores = my_strcat(scores, buffer);
        }
    fclose(fd);
    return (scores);
}

scoreboard_t scoreboard_create(env_t *env)
{
    scoreboard_t score;
    char *scores = create_score_from_file("Scoreboard");

    score.back = create_object("img/panel.png", VC{50, 200}, VC{0.5, 2});
    sfSprite_rotate(score.back.sprite, 90);
    if (env->langue[0] == 'E')
        score.title = setup_text("Scoreboard", "font/Xero.ttf", 40);
    if (env->langue[0] == 'F')
        score.title = setup_text("Tableau de score", "font/Xero.ttf", 30);
    sfText_setPosition(score.title.text, VC{-445, 225});
    if (scores == NULL) {
        score.data = setup_text("Invalid score file", "font/o_drift.ttf", 45);
        sfText_setPosition(score.data.text, VC{-425, 275});
    } else {
        score.data = setup_text(my_strdup(scores), "font/o_drift.ttf", 55);
        sfText_setPosition(score.data.text, VC{-345, 255});
    }
    return (score);
}

void scoreboard_display(SFWIN window, scoreboard_t score)
{
    if (pos_in_square(get_true_mouse_pos(window),
    sfSprite_getGlobalBounds(score.back.sprite))
    && sfSprite_getPosition(score.back.sprite).x < 515) {
        sfSprite_move(score.back.sprite, VC{5, 0});
        sfText_move(score.data.text, VC{5, 0});
        sfText_move(score.title.text, VC{5, 0});
    }
    if (pos_in_square(get_true_mouse_pos(window),
    sfSprite_getGlobalBounds(score.back.sprite)) == sfFalse
    && sfSprite_getPosition(score.back.sprite).x > 50) {
        sfSprite_move(score.back.sprite, VC{-5, 0});
        sfText_move(score.data.text, VC{-5, 0});
        sfText_move(score.title.text, VC{-5, 0});
    }
    sfRenderWindow_drawSprite(window, score.back.sprite, NULL);
    sfRenderWindow_drawText(window, score.title.text, NULL);
    sfRenderWindow_drawText(window, score.data.text, NULL);
}
