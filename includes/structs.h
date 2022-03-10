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
    int wave;
} player_stats;

typedef struct text_s {
    sfBool to_display;
    sfText *text;
    sfFont *font;
} text;

typedef struct button_s {
    sfSprite *sprite;
    sfTexture *texture;
    int already_hoverd;
    sfSound *hover;
    sfSoundBuffer *hover_buf;
    sfSound *click;
    sfSoundBuffer *click_buf;
    text text;
} button;

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

typedef struct turret_s {
    int type;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f position;
    int damage_speed;
    int damage_per_action;
    int range;
    struct turret_s *next;
} turret_t;

typedef struct pop_button_s {
    text titre;
    object icon;
    object onglet;
    turret_t *type;
} pop_button;

typedef struct map_block_s {
    int type;
    sfVector2f next_path;
    sfSprite *sprite;
    turret_t *turret;
} map_block;

typedef struct hud_s {
    object icon_health;
    object icon_energy;
    object icon_steel;
    object icon_energy_income_pos;
    object icon_steel_income_pos;
    object icon_energy_income_neu;
    object icon_steel_income_neu;
    object icon_energy_income_neg;
    object icon_steel_income_neg;
    text wave;
    text text_health;
    text text_energy;
    text text_steel;
    text text_energy_income;
    text text_steel_income;
    object cadre;
} hud;

typedef struct entities_s {
    enemy *enemies;
    turret_t *turrets;
} entities_t;

typedef struct current_game_s {
    enemy *enemies;
    turret_t *turrets;
    sfClock *clock;
    map_block **map;
    sfVector2f starting_square;
    player_stats player_stats;
} current_game_t;

typedef struct env_s {
    int volume;
    int fps;
    int vsync;
    int screen_type;
    char *langue;
    int resolution;
    sfClock *tempo;
    game_data data;
    current_game_t c_game;
} env_t;

#endif /* !STRUCT_H_ */
