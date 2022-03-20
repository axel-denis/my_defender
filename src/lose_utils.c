/*
** EPITECH PROJECT, 2022
** My_defender
** File description:
** lose_utils
*/

#include "csfml.h"
#include "lib.h"
#include "menu.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"

void free_lose_menu(text texte, text score, button *buttons)
{
    destroy_button(buttons[0]);
    destroy_button(buttons[1]);
    sfText_destroy(texte.text);
    sfText_destroy(score.text);
    sfFont_destroy(texte.font);
    sfFont_destroy(score.font);
}

char **scores_to_array(void)
{
    FILE *fd = fopen("Scoreboard", "r");
    char *buffer = NULL;
    size_t size = 0;
    char **current_scores;
    int len;

    if (fd == NULL)
        return NULL;
    for (len = 0; getline(&buffer, &size, fd) != -1 && len < 14; len++);
    fclose(fd);
    current_scores = malloc(sizeof(char *) * (len + 1));
    current_scores[len] = NULL;
    fd = fopen("Scoreboard", "r");
    for (int i = 0; getline(&buffer, &size, fd) != -1 && i < 14; i++) {
        current_scores[i] = my_strdup(buffer);
        current_scores[i][my_strlen(current_scores[i]) - 1] = '\0';
    }
    fclose(fd);
    return (current_scores);
}

void writting_score(env_t *env, int fd, int *written, char **current_scores)
{
    char *c_score = my_dec_to_base(env->c_game.player_stats.wave, "0123456789");

    for (int i = 0; current_scores[i] != NULL; i++) {
        if (my_get_nbr(current_scores[i]) > env->c_game.player_stats.wave
        || *written == 1) {
            write(fd, current_scores[i], my_strlen(current_scores[i]));
        } else {
            i--;
            write(fd, c_score, my_strlen(c_score));
            *written = 1;
        }
        write(fd, "\n", 1);
    }
    free(c_score);
}

void write_score_in_scoreboard(env_t *env)
{
    char **current_scores = scores_to_array();
    int fd = open("Scoreboard", O_WRONLY);
    int written = 0;
    char *c_score = my_dec_to_base(env->c_game.player_stats.wave, "0123456789");

    if (fd == -1)
        return;
    writting_score(env, fd, &written, current_scores);
    if (written == 0) {
        write(fd, c_score, my_strlen(c_score));
        write(fd, "\n", 1);
    }
    free(c_score);
    close(fd);
}
