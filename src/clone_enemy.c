/*
** EPITECH PROJECT, 2022
** My_defender
** File description:
** clone_enemy
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"
#include "map.h"
#include "maths.h"

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

void clone_enemy_dimentions(env_t *env, enemy to_clone, enemy *act)
{
    sfSprite_setScale(act->next->sprite, sfSprite_getScale(to_clone.sprite));
    sfSprite_setOrigin(act->next->sprite, sfSprite_getOrigin(to_clone.sprite));
    sfSprite_setPosition(act->next->sprite,
        VC{env->c_game.starting_square.x * TILE_SIZE + act->next->offset.x + 30,
        env->c_game.starting_square.y * TILE_SIZE + act->next->offset.y + 30});
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
    actual->next->disp = VC{0, 0};
    clone_enemy_dimentions(env, to_clone, actual);
    actual->next->texture = to_clone.texture;
    sfSprite_setTexture(actual->next->sprite, actual->next->texture, sfFalse);
    sfSprite_setOrigin(actual->next->sprite,
        VC{sfSprite_getGlobalBounds(actual->next->sprite).width / 2,
        sfSprite_getGlobalBounds(actual->next->sprite).height / 2});
    actual->next->cooldown = 0;
    actual->next->next = NULL;
}
