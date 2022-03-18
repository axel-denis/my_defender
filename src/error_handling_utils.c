/*
** EPITECH PROJECT, 2022
** My_defender
** File description:
** error_handling_utils
*/

#include "error_handling.h"

int is_a_file(char *name)
{
    FILE *file;

    name[my_strlen(name) - 1] = '\0';
    file = fopen(name, "r");
    if (file == NULL)
        return 84;
    fclose(file);
    return 0;
}

int string_is_valid_nbr(char *name, int could_be_zero)
{
    int len = my_strlen(name);

    if (len <= 1)
        return (84);
    for (int i = 0; i != len - 1; i++) {
        if (name[i] < '0' && name[i] > '9')
            return (84);
    }
    if (name[len - 1] != '\n')
        return (84);
    if (could_be_zero == 0 && my_get_nbr(name) == 0)
        return (84);
    return (0);
}

int has_correct_size(int correct_size, char *file)
{
    size_t size = 0;
    FILE *fd = fopen(file, "r");
    char *buffer = NULL;
    int len;

    for (len = 0; getline(&buffer, &size, fd) != -1; len++);
    if (len != correct_size)
        return (84);
    return (0);
    fclose(fd);
}
