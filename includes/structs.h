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
    sfVector2i energy;
    sfVector2i energy_income;
    sfVector2i steel;
    sfVector2i steel_income;
    int health;
    int score;
} player_stats;

typedef struct text_s {
    sfBool to_display;
    sfText *text;
    sfFont *font;
} text;

typedef struct button_s {
    sfSprite *sprite;
    sfTexture *texture;
    text text;
    // peut être faire un pointeur sur fonction
} button;

typedef struct map_block_s {
    int type;
    sfVector2f next_path;
    sfSprite *sprite;
    turret *turret;
} map_block;

typedef struct game_data_s {
    sfTexture *ground_texture;
    sfTexture *path_texture;
    sfMusic *music;
} game_data;

typedef struct enemy_s {
    int type;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f disp;
    float speed;
    int health;
    struct enemy_s *next;
} enemy;

typedef struct env_s {
    map_block **map;
    int volume;
    char *langue;
    sfVector2f starting_square;
    player_stats player_stats;
    game_data data;
    enemy *enemies;
} env_t;


#endif /* !STRUCT_H_ */
