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
