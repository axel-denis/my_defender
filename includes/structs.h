/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** structs.h
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include "csfml.h"

    #define VC (sfVector2f)

typedef struct object_s {
    sfSprite *sprite;
    sfTexture *texture;
}object;

typedef struct enemy_s {
    int type;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f position;
    sfVector2f objective;
    int objective_index; // pour savoir à quel point de position il en est
    int health;
    int speed;
} enemy;

typedef struct turret_s {
    int type;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f position;
    int damage_speed;
    int damage_per_action;
} turret;

typedef struct map_s {
    int index;
    sfVector2f *path_list;
} map;

typedef struct player_stats_s {
    int energy;
    int iron;
    int score;
    int health;
} player_stats;

typedef struct text_s {
    sfBool to_display;
    sfText *text;
    sfFont *font;
}text;

typedef struct button_s {
    sfSprite *sprite;
    sfTexture *texture;
    text text;
    sfBool is_hovered;
    sfBool is_clicked;
    // peut être faire un pointeur sur fonction
} button;

#endif /* !STRUCT_H_ */
