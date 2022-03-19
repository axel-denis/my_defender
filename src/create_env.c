/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** create_env.c
*/

#include "csfml.h"
#include "structs.h"
#include "lib.h"

void create_env_playerstats(env_t *env)
{
    env->c_game.player_stats.wave = 1;
    env->c_game.enemies = NULL;
    env->c_game.turrets = NULL;
    env->c_game.bullets = NULL;
    env->c_game.clock = sfClock_create();
}

env_t *create_env(void)
{
    env_t *env = malloc(sizeof(env_t));

    env->tempo = sfClock_create();
    env->fps = 75;
    env->screen_type = 2;
    env->vsync = 1;
    env->resolution = 1920;
    env->data.music = sfMusic_createFromFile("sounds/uncharted-worlds.ogg");
    sfMusic_play(env->data.music);
    sfMusic_setLoop(env->data.music, sfTrue);
    env->volume = 100;
    sfMusic_setVolume(env->data.music, env->volume / 2);
    env->langue = my_strdup("EN");
    env->data.ground_texture =
        sfTexture_createFromFile("img/grass.png", NULL);
    env->data.path_texture = sfTexture_createFromFile("img/dirt.png", NULL);
    env->data.bullet_texture = SFTEXTFILE("img/base_arrow.png", NULL);
    create_env_playerstats(env);
    return env;
}
