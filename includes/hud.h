/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** hud
*/

#ifndef HUD_H_
    #define HUD_H_

    #include "csfml.h"
    #include "structs.h"

void display_hud(hud hud_p, env_t *env, sfRenderWindow *window);
hud create_hud(void);
char *formating_hud(int value);
char *formating_hud_in(int value);
hud update_hud(hud hud_player, env_t *env);
void update_player_data(env_t *env, sfClock *clock);

#endif
