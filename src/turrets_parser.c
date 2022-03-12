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

turret_t create_turret_from_file(char *titre)
{
    char *file = malloc(sizeof(char) * (1 + my_strlen(titre) + 8));
    my_strcpy(file, "turrets/");
    char **texture;
    my_strcat(file, titre);
    FILE *fd = fopen(file, "r");
    size_t size = 0;
    char *buffer = NULL;
    turret_t returned;

    returned.name = my_strdup(titre);
    for (int i = 0; getline(&buffer, &size, fd) != -1; i++) {
        if (i == 0)
            returned.damage_speed = my_get_nbr(buffer);
        if (i == 1)
            returned.damage_per_action = my_get_nbr(buffer);
        if (i == 2) {
            texture = my_split(buffer, '\n');
            returned.texture = sfTexture_createFromFile(texture[0], NULL);
        }
        if (i == 3)
            returned.type = my_get_nbr(buffer);
        if (i == 4)
            returned.range = my_get_nbr(buffer);
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

turret_t *create_turret_type(void)
{
    turret_t *turrets = malloc(sizeof(turret_t) * (count_files_in_folder("turrets") + 1));
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
            turrets[number] = create_turret_from_file(dir->d_name);
            number += 1;
        }
    }
    turrets[number] = *(create_null_turret());
    closedir(fd);
    return turrets;
}
