/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** enemy_parser
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "turrets.h"
#include "files.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

turret_t create_turret_from_file(env_t *env, char *titre)
{
    char *file = malloc(sizeof(char) * (1 + my_strlen(titre) + 8));
    my_strcpy(file, "turrets/");
    char **texture;
    my_strcat(file, titre);
    FILE *fd = fopen(file, "r");
    size_t size = 0;
    char *buffer = NULL;
    turret_t returned;

    returned.name_upgrade1 = NULL;
    returned.name_upgrade2 = NULL;
    if (env->langue[0] == 'E')
        returned.name = my_strdup(titre);
    for (int i = 0; getline(&buffer, &size, fd) != -1; i++) {
        if (env->langue[0] != 'E' && i == 0)
            returned.name = my_strdup(buffer);
        if (i == 1)
            returned.damage_speed = my_get_nbr(buffer);
        if (i == 2)
            returned.damage_per_action = my_get_nbr(buffer);
        if (i == 3) {
            texture = my_split(buffer, '\n');
            returned.texture = sfTexture_createFromFile(texture[0], NULL);
        }
        if (i == 4)
            returned.type = my_get_nbr(buffer);
        if (i == 5)
            returned.range = my_get_nbr(buffer);
        if (i == 6)
            returned.energy_cost = my_get_nbr(buffer);
        if (i == 7)
            returned.steel_cost = my_get_nbr(buffer);
        if (i == 8)
            returned.energy_per_s = my_get_nbr(buffer);
        if (i == 9)
            returned.steel_per_s = my_get_nbr(buffer);
        if (i == 10)
            if (my_strcmp(buffer, "NULL\n") != 0)
                returned.name_upgrade1 = my_strdup(buffer);
        if (i == 11)
            if (my_strcmp(buffer, "NULL\n") != 0)
                returned.name_upgrade2 = my_strdup(buffer);
        if (i == 12)
            returned.is_base = my_get_nbr(buffer);
    }
    returned.sprite = sfSprite_create();
    sfSprite_setTexture(returned.sprite, returned.texture, sfFalse);
    for (int i = 0; texture[i] != NULL; i++)
        free(texture[i]);
    free(texture);
    free(file);
    fclose(fd);
    return (returned);
}

turret_t *create_turret_type(env_t *env)
{
    turret_t *turrets = malloc(sizeof(turret_t) * (count_files("turrets") + 1));
    int conti = 1;
    struct dirent *dir;
    DIR *fd = opendir("turrets");
    int number = 0;

    if (fd == NULL)
        return (NULL);
    for (int i = 0; conti == 1; i++) {
        dir = readdir(fd);
        if (dir == NULL)
            conti = 0;
        if (dir != NULL && dir->d_name[0] != '.') {
            turrets[number] = create_turret_from_file(env, dir->d_name);
            number += 1;
        }
    }
    turrets[number] = *(create_null_turret());
    closedir(fd);
    return turrets;
}
