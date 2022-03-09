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
hud create_hud(env_t *env);
char *formating_hud(sfVector2i value);
hud update_hud(hud hud_player, env_t *env);

#endif /* !HUD_H_ */
