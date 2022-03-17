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

#define TILE_SIZE 60
#define SIGN(x) (x > 0 ? 1 : -1)
#define nextpath env->c_game.map[(int) pos.y / 60][(int) pos.x / 60].next_path
#define nextpath_type env->c_game.map[(int) pos.y / 60][(int) pos.x / 60].type

void clone_base_e_data(enemy *to_clone, enemy *new)
{
    new->difficulty = to_clone->difficulty;
    new->health = to_clone->health;
    new->name = to_clone->name;
    new->speed = to_clone->speed;
    new->type = to_clone->type;
    new->age = 0;
    new->offset = VC{rand() % 30 - 15, rand() % 30 - 15};
    new->sprite = sfSprite_create();
}

void clone_enemy(env_t *env, enemy to_clone)
{
    enemy *actual = env->c_game.enemies;

    if (actual == NULL)
        env->c_game.enemies = create_null_enemy();
    actual = env->c_game.enemies;
    actual = last_e_link(actual);
    actual->next = malloc(sizeof(enemy));
    clone_base_e_data(&to_clone, actual->next);
    sfSprite_setScale(actual->next->sprite, sfSprite_getScale(to_clone.sprite));
    sfSprite_setOrigin(actual->next->sprite, sfSprite_getOrigin(to_clone.sprite));
    actual->next->disp = VC{0, 0};
    sfSprite_setPosition(actual->next->sprite,
        VC{env->c_game.starting_square.x * TILE_SIZE + actual->next->offset.x + 30,
        env->c_game.starting_square.y * TILE_SIZE + actual->next->offset.y + 30});
    actual->next->texture = to_clone.texture;
    sfSprite_setTexture(actual->next->sprite, actual->next->texture, sfFalse);
    sfSprite_setOrigin(actual->next->sprite,
        VC{sfSprite_getGlobalBounds(actual->next->sprite).width / 2,
        sfSprite_getGlobalBounds(actual->next->sprite).height / 2});
    actual->next->next = NULL;
}

void point_mob_towards_next_tile(env_t *env, sfVector2f pos, enemy *mob)
{
    mob->age++;
    if (nextpath_type == 5) {
        mob->disp.x = 512;
    } else {
        mob->disp.x = ((nextpath.x * 60 > pos.x) -
            (nextpath.x * 60 < pos.x)) * 60;
        mob->disp.y = ((nextpath.y * 60 > pos.y) -
            (nextpath.y * 60 < pos.y)) * 60;
    }
}

void evolve_enemy(env_t *env, enemy *mob)
{
    sfVector2f pos = sfSprite_getPosition(mob->sprite);
    sfVector2f movement = {0, 0};

    if (sfTime_asMilliseconds(sfClock_getElapsedTime(env->tempo))
        - mob->cooldown < 0.013)
        return;
    mob->cooldown = sfTime_asMilliseconds(sfClock_getElapsedTime(env->tempo));
    pos.x = pos.x - mob->offset.x - 30;
    pos.y = pos.y - mob->offset.y - 30;
    if (mob->disp.x == 0 && mob->disp.y == 0) {
        point_mob_towards_next_tile(env, pos, mob);
    }
    movement.x = MIN(ABS(mob->disp.x), mob->speed) * SIGN(mob->disp.x);
    movement.y = MIN(ABS(mob->disp.y), mob->speed) * SIGN(mob->disp.y);
    mob->disp.x -= movement.x;
    mob->disp.y -= movement.y;
    sfSprite_move(mob->sprite, movement);
}

enemy *get_oldest(env_t *env, turret_t *turret)
{
    enemy *actual = env->c_game.enemies;
    enemy *output = NULL;
    sfVector2f pos = sfSprite_getPosition(turret->sprite);
    sfVector2f act_pos;
    int age = 0;

    while (actual != NULL) {
        if (actual->type == 0) {
            actual = actual->next;
            continue;
        }
        act_pos = sfSprite_getPosition(actual->sprite);
        if (dist_two_points(act_pos, pos) < turret->range
            && actual->age > age) {
            age = actual->age;
            output = actual;
        }
        actual = actual->next;
    }
    return output;
}
