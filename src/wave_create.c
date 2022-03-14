/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** wave_create
*/

#include "enemy.h"
#include "csfml.h"
#include "lib.h"
#include "structs.h"

int exist_smaller(enemy *enemies_type, double place_available_for_him) {
    int found_smaller = 0;

    for (int j = 0; enemies_type[j].sprite != NULL; j++)
        if (enemies_type[j].difficulty <= place_available_for_him)
            found_smaller = 1;
    if (found_smaller == 1)
        return 0;
    return 1;
}

void first_adding_ennemies(enemy *enemies_type, wave_t *wave, int nb, int len)
{
    int what_ennemie = -1;
    int place_available_for_him = nb;
    int open = 1;

    while (open) {
        if (exist_smaller(enemies_type, place_available_for_him) == 0)
            open = 0;
        else
            place_available_for_him += 1;
    }
    do {
        what_ennemie = rand() % len;
    } while (place_available_for_him < enemies_type[what_ennemie].difficulty);
    for (int j = 0; place_available_for_him > 0; j++) {
        place_available_for_him -= enemies_type[what_ennemie].difficulty;
        wave->nbr1 += 1;
    }
    wave->type1 = what_ennemie;
}

void second_adding_ennemies(enemy *enemies_type, wave_t *wave, int nb, int len)
{
    int what_ennemie = -1;
    int place_available_for_him = nb;
    int open = 1;

    while (open) {
        if (exist_smaller(enemies_type, place_available_for_him) == 0)
            open = 0;
        else
            place_available_for_him += 1;
    }
    do {
        what_ennemie = rand() % len;
    } while (place_available_for_him < enemies_type[what_ennemie].difficulty);
    for (int j = 0; place_available_for_him > 0; j++) {
        place_available_for_him -= enemies_type[what_ennemie].difficulty;
        wave->nbr2 += 1;
    }
    wave->type2 = what_ennemie;
}

wave_t wave_create(env_t *env, enemy *enemies_type)
{
    int nbr_a = 10 * env->c_game.player_stats.wave / 5;
    int nbr_t = 1 + rand() % 3;
    wave_t current_wave = {0, 0, 0, 0};
    int len;

    for (len = 0; enemies_type[len].sprite != NULL; len++);
    first_adding_ennemies(enemies_type, &current_wave, nbr_a / nbr_t, len);
    if (nbr_t == 2)
        second_adding_ennemies(enemies_type, &current_wave, nbr_a / nbr_t, len);
    else {
        current_wave.nbr2 = 0;
        current_wave.type2 = 0;
    }
    return (current_wave);
}
