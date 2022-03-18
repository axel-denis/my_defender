/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** enemy_parser
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "enemy.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int count_files(char *name)
{
    int conti = 1;
    int nbr = 0;
    DIR *fd = opendir(name);
    struct dirent *dir;

    for (int i = 0; conti == 1; i++) {
        dir = readdir(fd);
        if (dir == NULL)
            conti = 0;
        if (dir != NULL && dir->d_name[0] != '.')
            nbr += 1;
    }
    closedir(fd);
    return (nbr);
}

enemy *create_enemies_type(void)
{
    enemy *enemies = malloc(sizeof(enemy) * (count_files("enemies") + 1));
    int conti = 1;
    struct dirent *dir;
    DIR *fd = opendir("enemies");
    int number = 0;

    if (fd == NULL)
        return (NULL);
    for (int i = 0; conti == 1; i++) {
        dir = readdir(fd);
        if (dir == NULL)
            conti = 0;
        if (dir != NULL && dir->d_name[0] != '.') {
            enemies[number] = create_enemy_from_file(dir->d_name);
            number += 1;
        }
    }
    enemies[number] = *(create_null_enemy());
    closedir(fd);
    return enemies;
}
