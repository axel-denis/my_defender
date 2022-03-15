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

int error_handling(char *name)
{
    int conti = 1;
    int nbr = 0;
    DIR *fd = opendir(name);
    struct dirent *dir;

    if (fd == NULL) {
        write(2, "config folder missing\n", 22);
        return (84);
    }
    for (int i = 0; conti == 1; i++) {
        dir = readdir(fd);
        if (dir == NULL)
            conti = 0;
        if (dir != NULL && dir->d_name[0] != '.')
            nbr += 1;
    }
    closedir(fd);
    if (nbr < 1)
        return (84);
    return (0);
}

enemy create_enemy_from_file(char *titre)
{
    char *file = malloc(sizeof(char) * (1 + my_strlen(titre) + 8));
    my_strcpy(file, "enemies/");
    char **texture;
    my_strcat(file, titre);
    FILE *fd = fopen(file, "r");
    size_t size = 0;
    int speed = 0;
    char *buffer = NULL;
    sfVector2f scale;
    enemy returned;

    returned.sprite = sfSprite_create();
    returned.name = my_strdup(titre);
    for (int i = 0; getline(&buffer, &size, fd) != -1; i++) {
        if (i == 0)
            returned.health = my_get_nbr(buffer);
        if (i == 1)
            speed = my_get_nbr(buffer);
        if (i == 2)
            returned.speed = speed / my_get_nbr(buffer);
        if (i == 3) {
            texture = my_split(buffer, '\n');
            returned.texture = sfTexture_createFromFile(texture[0], NULL);
        }
        if (i == 4)
            returned.type = my_get_nbr(buffer);
        if (i == 5)
            returned.difficulty = my_get_nbr(buffer);
        if (i == 6) {
            scale = sfSprite_getScale(returned.sprite);
            sfSprite_setScale(returned.sprite, VC{(float) my_get_nbr(buffer) / 1000, scale.y});
        }
        if (i == 7) {
            scale = sfSprite_getScale(returned.sprite);
            sfSprite_setScale(returned.sprite, VC{scale.x, (float) my_get_nbr(buffer) / 1000});
        }
    }
    sfSprite_setOrigin(returned.sprite, VC{sfSprite_getGlobalBounds(returned.sprite).width / 2, sfSprite_getGlobalBounds(returned.sprite).height / 2});
    sfSprite_setTexture(returned.sprite, returned.texture, sfFalse);
    for (int i = 0; texture[i] != NULL; i++)
        free(texture[i]);
    free(texture);
    fclose(fd);
    return (returned);
}

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
