/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** ennemy
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"
#include "maths.h"

#define nextpath env->c_game.map[(int) pos.y / 60][(int) pos.x / 60].next_path

enemy *create_null_enemy(void)
{
    enemy *output = malloc(sizeof(enemy));

    output->disp = VC{0, 0};
    output->health = 1;
    output->speed = 0;
    output->sprite = NULL;
    output->texture = NULL;
    output->type = 0;
    output->next = NULL;
    return output;
}

enemy *template_enemy(int type, int speed, int health)
{
    enemy *output = malloc(sizeof(enemy));

    output->type = type;
    output->speed = speed;
    output->health = health;
    return output;
}

void clone_enemy(env_t *env, enemy to_clone)
{
    enemy *actual = env->c_game.enemies;

    if (actual == NULL) {
        env->c_game.enemies = create_null_enemy();
        actual = env->c_game.enemies;
    }
    while (actual->next != NULL)
        actual = actual->next;
    actual->next = malloc(sizeof(enemy));
    actual->next->difficulty = to_clone.difficulty;
    actual->next->health = to_clone.health;
    actual->next->name = to_clone.name;
    actual->next->speed = to_clone.speed;
    actual->next->type = to_clone.type;
    actual->next->sprite = sfSprite_create();
    sfSprite_setScale(actual->next->sprite, sfSprite_getScale(to_clone.sprite));
    sfSprite_setOrigin(actual->next->sprite, sfSprite_getOrigin(to_clone.sprite));
    actual->next->disp = VC{0, 0};
    sfSprite_setPosition(actual->next->sprite, VC{env->c_game.starting_square.x * 60 + 30 + rand() % 30 - 15, env->c_game.starting_square.y * 60 + 30 + rand() % 30 - 15});
    actual->next->texture = to_clone.texture;
    sfSprite_setTexture(actual->next->sprite, actual->next->texture, sfFalse);
    sfSprite_setOrigin(actual->next->sprite, VC{sfSprite_getGlobalBounds(actual->next->sprite).width / 2, sfSprite_getGlobalBounds(actual->next->sprite).height / 2});
    actual->next->next = NULL;
}

void create_enemy_type_1(env_t *env)
{
    enemy *actual = env->c_game.enemies;

    if (actual == NULL) {
        env->c_game.enemies = create_null_enemy();
        actual = env->c_game.enemies;
    }
    while (actual->next != NULL)
        actual = actual->next;
    actual->next = template_enemy(1, 4, 100);
    actual->next->sprite = sfSprite_create();
    actual->next->disp = VC{0, 0};
    sfSprite_setPosition(actual->next->sprite, VC{env->c_game.starting_square.x * 60 + 30 + rand() % 30 - 15, env->c_game.starting_square.y * 60 + 30 + rand() % 30 - 15});
    actual->next->texture = sfTexture_createFromFile("img/type1.png", NULL);
    sfSprite_setTexture(actual->next->sprite, actual->next->texture, sfFalse);
    sfSprite_setOrigin(actual->next->sprite, VC{sfSprite_getGlobalBounds(actual->next->sprite).width / 2, sfSprite_getGlobalBounds(actual->next->sprite).height / 2});
    actual->next->next = NULL;
}

void create_test_enemy(env_t *env, int health)
{
    enemy *actual = env->c_game.enemies;

    if (actual == NULL) {
        env->c_game.enemies = create_null_enemy();
        actual = env->c_game.enemies;
    }
    while (actual->next != NULL)
        actual = actual->next;
    actual->next = template_enemy(1, 1, health);
    actual->next->sprite = sfSprite_create();
    actual->next->disp = VC{0, 0};
    sfSprite_setPosition(actual->next->sprite, VC{env->c_game.starting_square.x * 60 + 30 + rand() % 30 - 15, env->c_game.starting_square.y * 60 + 30 + rand() % 30 - 15});
    actual->next->texture = sfTexture_createFromFile("img/type1.png", NULL);
    sfSprite_setTexture(actual->next->sprite, actual->next->texture, sfFalse);
    sfSprite_setOrigin(actual->next->sprite, VC{sfSprite_getGlobalBounds(actual->next->sprite).width / 2, sfSprite_getGlobalBounds(actual->next->sprite).height / 2});
    actual->next->next = NULL;
}

#define MIN(x, y) (y < x) ? y : x

void evolve_enemy(env_t *env, enemy *mob)
{
    sfVector2f pos = sfSprite_getPosition(mob->sprite);
    sfVector2f movement = {0, 0};

    if (mob->disp.x == 0 && mob->disp.y == 0 &&
        pos.x < MAP_LEN * 60 - 15 && pos.y < MAP_HEIGHT * 60 - 15) {
        mob->disp.x = ((nextpath.x > get_case_coords(pos).x) - (nextpath.x < get_case_coords(pos).x));
        mob->disp.y = ((nextpath.y > get_case_coords(pos).y) - (nextpath.y < get_case_coords(pos).y));
        mob->disp.x *= 1 / mob->speed * 60;
        mob->disp.y *= 1 / mob->speed * 60;
    }

    movement.x = ((mob->disp.x > 0) - (mob->disp.x < 0)) * (MIN(mob->speed, (ABS(mob->disp.x))));
    movement.y = ((mob->disp.y > 0) - (mob->disp.y < 0)) * (MIN(mob->speed, (ABS(mob->disp.y))));
    mob->disp.x += ((mob->disp.x < 0) - (mob->disp.x > 0)) * (MIN(mob->speed, (ABS(mob->disp.x))));
    mob->disp.y += ((mob->disp.y < 0) - (mob->disp.y > 0)) * (MIN(mob->speed, (ABS(mob->disp.y))));
    sfSprite_move(mob->sprite, movement);
}

enemy *get_nearest(env_t *env, sfVector2f pos)
{
    enemy *actual = env->c_game.enemies;
    enemy *output = NULL;
    float nearest = 2000;
    sfVector2f act_pos;

    while (actual != NULL) {
        if (actual->type == 0) {
            actual = actual->next;
            continue;
        }
        act_pos = sfSprite_getPosition(actual->sprite);
        if (dist_two_points(act_pos, pos) < nearest && actual->type != 0) {
            nearest = dist_two_points(act_pos, pos);
            output = actual;
        }
        actual = actual->next;
    }
    return output;
}
