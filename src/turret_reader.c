/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** turret_reader.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "turrets.h"
#include "files.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void get_tur_first_data(turret_t *out, int data_index, char *buf, char ***tex)
{
    if (data_index == 1)
        out->damage_speed = my_get_nbr(buf);
    if (data_index == 2)
        out->damage_per_action = my_get_nbr(buf);
    if (data_index == 3) {
        *tex = my_split(buf, '\n');
        out->texture = sfTexture_createFromFile((*tex)[0], NULL);
    }
    if (data_index == 4)
        out->type = my_get_nbr(buf);
}

void get_turret_last_data(turret_t *returned, int indx, char *buffer, env_t *ev)
{
    turret_t *next;

    buffer[my_strlen(buffer) - 1] = '\0';
    if (indx == 5)
        returned->range = my_get_nbr(buffer);
    if (indx == 6)
        returned->energy_cost = my_get_nbr(buffer);
    if (indx == 7)
        returned->steel_cost = my_get_nbr(buffer);
    if (indx == 8)
        returned->energy_per_s = my_get_nbr(buffer);
    if (indx == 9)
        returned->steel_per_s = my_get_nbr(buffer);
    if (indx == 10 && my_strcmp(buffer, "NULL") != 0) {
        next = create_malloc_turret_from_file(ev, buffer);
        returned->upgrade_1 = next;
    } else if (indx == 11 && my_strcmp(buffer, "NULL") != 0) {
        next = create_malloc_turret_from_file(ev, buffer);
        returned->upgrade_2 = next;
    }
}

void setup_turret_data(env_t *env, char *file, turret_t *returned, char ***tex)
{
    FILE *fd = fopen(file, "r");
    char *buffer = NULL;
    size_t size = 0;

    for (int i = 0; getline(&buffer, &size, fd) != -1; i++) {
        if (env->langue[0] != 'E' && i == 0)
            returned->name = my_strdup(buffer);
        get_tur_first_data(returned, i, buffer, tex);
        get_turret_last_data(returned, i, buffer, env);
    }
    fclose(fd);
}

turret_t *create_malloc_turret_from_file(env_t *env, char *titre)
{
    char *file = malloc(sizeof(char) * (1 + my_strlen(titre) + 8));
    char **texture;
    turret_t *returned = malloc(sizeof(turret_t));

    my_strcpy(file, "turrets/");
    my_strcat(file, titre);
    if (env->langue[0] == 'E')
        returned->name = my_strdup(titre);
    setup_turret_data(env, file, returned, &texture);
    returned->sprite = sfSprite_create();
    sfSprite_setTexture(returned->sprite, returned->texture, sfFalse);
    for (int i = 0; texture[i] != NULL; i++)
        free(texture[i]);
    free(texture);
    free(file);
    return (returned);
}

turret_t create_turret_from_file(env_t *env, char *titre)
{
    char *file = malloc(sizeof(char) * (1 + my_strlen(titre) + 8));
    char **texture;
    turret_t returned;

    my_strcpy(file, "turrets/");
    my_strcat(file, titre);
    if (env->langue[0] == 'E')
        returned.name = my_strdup(titre);
    setup_turret_data(env, file, &returned, &texture);
    returned.sprite = sfSprite_create();
    sfSprite_setTexture(returned.sprite, returned.texture, sfFalse);
    for (int i = 0; texture[i] != NULL; i++)
        free(texture[i]);
    free(texture);
    free(file);
    return (returned);
}
