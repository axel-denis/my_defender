/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** enemy_reader.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void get_first_data(enemy *returned, int data_index, char *buffer, char ***tex)
{
    if (data_index == 0)
        returned->health = my_get_nbr(buffer);
    if (data_index == 1)
        returned->speed = my_get_nbr(buffer);
    if (data_index == 2)
        returned->speed = returned->speed / my_get_nbr(buffer);
    if (data_index == 3) {
        *tex = my_split(buffer, '\n');
        returned->texture = sfTexture_createFromFile((*tex)[0], NULL);
    }
    if (data_index == 4)
        returned->type = my_get_nbr(buffer);
}

void get_last_data(enemy *returned, int data_index, char *buffer)
{
    sfVector2f scale;

    if (data_index == 5)
        returned->difficulty = my_get_nbr(buffer);
    if (data_index == 6) {
        scale = sfSprite_getScale(returned->sprite);
        sfSprite_setScale(returned->sprite,
            VC{(float) my_get_nbr(buffer) / 1000, scale.y});
    }
    if (data_index == 7) {
        scale = sfSprite_getScale(returned->sprite);
        sfSprite_setScale(returned->sprite,
            VC{scale.x, (float) my_get_nbr(buffer) / 1000});
    }
}

void setup_enemy_data(char *buffer, enemy *returned, char *file, char ***tex)
{
    FILE *fd = fopen(file, "r");
    size_t size = 0;

    for (int i = 0; getline(&buffer, &size, fd) != -1; i++) {
        get_first_data(returned, i, buffer, tex);
        get_last_data(returned, i, buffer);
    }
    sfSprite_setOrigin(returned->sprite, VC{sfSprite_getGlobalBounds(
        returned->sprite).width / 2,
        sfSprite_getGlobalBounds(returned->sprite).height / 2});
    sfSprite_setTexture(returned->sprite, returned->texture, sfFalse);
    fclose(fd);
}

enemy create_enemy_from_file(char *titre)
{
    char *file = malloc(sizeof(char) * (1 + my_strlen(titre) + 8));
    my_strcpy(file, "enemies/");
    my_strcat(file, titre);
    char *buffer = NULL;
    char **texture;
    enemy returned;

    returned.sprite = sfSprite_create();
    returned.name = my_strdup(titre);
    setup_enemy_data(buffer, &returned, file, &texture);
    for (int i = 0; texture[i] != NULL; i++)
        free(texture[i]);
    free(texture);
    return (returned);
}
