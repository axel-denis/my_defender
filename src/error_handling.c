/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** error_handling
*/

#include "error_handling.h"

int error_file_turrets(char *titre)
{
    char *file = malloc(sizeof(char) * (1 + my_strlen(titre) + 8));
    my_strcpy(file, "turrets/");
    my_strcat(file, titre);
    int return_val = has_correct_size(13, file);
    size_t size = 0;
    char *buffer = NULL;
    FILE *fd = fopen(file, "r");

    for (int i = 0; getline(&buffer, &size, fd) != -1; i++) {
        if (i <= 9 && i >= 6)
            return_val += string_is_valid_nbr(buffer, 1);
        if (i != 0 && i != 3 && (i > 12 || i < 6))
            return_val += string_is_valid_nbr(buffer, 0);
        if (i == 3 || i == 10 || i == 11)
            return_val += is_a_file(buffer);
    }
    fclose(fd);
    return (return_val);
}

int error_file_ennemies(char *titre)
{
    char *file = malloc(sizeof(char) * (1 + my_strlen(titre) + 8));
    my_strcpy(file, "enemies/");
    my_strcat(file, titre);
    int return_val = has_correct_size(8, file);
    size_t size = 0;
    char *buffer = NULL;
    FILE *fd = fopen(file, "r");

    for (int i = 0; getline(&buffer, &size, fd) != -1; i++) {
        if (i != 3)
            return_val += string_is_valid_nbr(buffer, 0);
        else
            return_val += is_a_file(buffer);
    }
    fclose(fd);
    return (return_val);
}

int error_opener(char *name)
{
    int conti = 1;
    int retur_val = 0;
    DIR *fd = opendir(name);
    struct dirent *dir;

    for (int i = 0; conti == 1; i++) {
        dir = readdir(fd);
        if (dir == NULL)
            conti = 0;
        if (dir != NULL && dir->d_name[0] != '.' && name[0] == 'e')
            retur_val += error_file_ennemies(dir->d_name);
        if (dir != NULL && dir->d_name[0] != '.' && name[0] == 't') {
            retur_val += error_file_turrets(dir->d_name);
        }
    }
    closedir(fd);
    return (retur_val);
}

int error_folder(char *name)
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

int error_handling(void)
{
    if (error_folder("enemies") == 84 || error_folder("turrets") == 84)
        return (84);
    if (error_opener("enemies") > 0)
        return (84);
    if (error_opener("turrets") > 0)
        return (84);
    return (0);
}
