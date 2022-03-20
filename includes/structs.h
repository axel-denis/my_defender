/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** structs.h
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>

    #define VC (sfVector2f)

typedef struct object_s {
    sfSprite *sprite;
    sfTexture *texture;
} object;

typedef struct wave_s {
    int type1;
    int nbr1;
    int type2;
    int nbr2;
} wave_t;

typedef struct map_s {
    int index;
    sfVector2f *path_list;
} map;

typedef struct player_stats_s {
    int energy;
    int energy_income;
    int steel;
    int steel_income;
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
    sfTexture *bullet_texture;
    sfMusic *music;
} game_data;

typedef struct enemy_s {
    int type;
    int age;
    int cooldown;
    int slowed_time;
    sfVector2f offset;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f disp;
    float speed;
    int health;
    int difficulty;
    char *name;
    struct enemy_s *next;
} enemy;

typedef struct turret_s {
    int type;
    char *name;
    int cooldown;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f position;
    int damage_speed;
    int damage_per_action;
    float range;
    int energy_cost;
    int energy_per_s;
    int steel_cost;
    int steel_per_s;
    struct turret_s *next;
    struct turret_s *upgrade_1;
    struct turret_s *upgrade_2;
    int is_base;
} turret_t;

typedef struct pop_button_s {
    text titre;
    text energy_cost;
    text energy_per_s;
    text steel_cost;
    text steel_per_s;
    object icon;
    object onglet;
    object energy;
    object steel;
    object energy_income_pos;
    object steel_income_pos;
    object energy_income_neu;
    object steel_income_neu;
    object energy_income_neg;
    object steel_income_neg;
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

typedef struct bullet_s {
    int is_null;
    int type;
    float speed;
    int damage;
    sfVector2f direction;
    enemy *target;
    turret_t *shooter;
    sfSprite *sprite;
    struct bullet_s *next;
} bullet_t;

typedef struct current_game_s {
    enemy *enemies;
    turret_t *turrets;
    bullet_t *bullets;
    sfClock *wave_timer;
    sfClock *clock;
    map_block **map;
    sfVector2f starting_square;
    player_stats player_stats;
} current_game_t;

typedef struct upgrade_menu_s {
    turret_t *upgrading;
    text name_1;
    text name_2;
    object icon_energy_1;
    object icon_steel_1;
    object icon_energy_2;
    object icon_steel_2;
    text cost_energy_1;
    text cost_steel_1;
    text cost_energy_2;
    text cost_steel_2;
    object back;
    button close;
} upgrade_menu_t;

typedef struct env_s {
    int volume;
    int fps;
    int vsync;
    int screen_type;
    char *langue;
    int resolution;
    int *keys;
    sfClock *tempo;
    game_data data;
    current_game_t c_game;
} env_t;

typedef struct game_data {
    enemy *enemies_type;
    wave_t wave;
    upgrade_menu_t upgrade;
    sfClock *clock;
    hud hud_player;
    object background;
    object worm_hole;
    object worm_hole2;
    sfCircleShape *range;
    pop_button *buttons;
} game_data_t;

typedef struct scoreboard_s {
    object back;
    text title;
} scoreboard_t;

typedef struct menu_s {
    button *buttons;
    object background;
    text texte;
    scoreboard_t score;
} menu_t;

#endif
