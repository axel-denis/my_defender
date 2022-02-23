/*
** EPITECH PROJECT, 2021
** my_strcpy
** File description:
** copy a str into a 2nd str
*/

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (i; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return (dest);
}
