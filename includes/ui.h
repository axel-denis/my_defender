/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ui
*/

#ifndef UI_H_
    #define UI_H_

pop_button *create_turret_button_ui(void);
void display_turret_icon(pop_button *buttons, sfRenderWindow *window, int i);
void display_turrets_button_ui(pop_button *buttons, sfRenderWindow *window, int pickedup, env_t *env);
int pickup_turrets(pop_button *but, sfVector2f mouse_pos, int pick, env_t *env);
void display_picked_turret(int pickedup, pop_button *buttons, sfRenderWindow *w);

#endif /* !UI_H_ */
