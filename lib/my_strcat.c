/*
** EPITECH PROJECT, 2021
** cpoolday7
** File description:
** concatenates two string
*/

int my_strlen(char const *str);

char *my_strcat(char *dest , char const *src)
{
    int len = my_strlen(dest);

    for (int i = 0; src[i] != '\0'; i++)
        dest[len + i] = src[i];
    dest[len + my_strlen(src)] = '\0';
    return (dest);
}
