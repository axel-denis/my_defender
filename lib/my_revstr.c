/*
** EPITECH PROJECT, 2021
** cpoolday06
** File description:
** reverse the str
*/

char *my_revstr(char *str)
{
    int i = 0;
    int j = 0;

    while (str[j] != '\0')
        j++;
    char dest[j];

    while (str[i] != '\0') {
        dest[i] = str[i];
        i++;
    }
    i = 0;
    while (str[i] != '\0') {
        str[i] = dest[j - i - 1];
        i++;
    }
    dest[i] = '\0';
    return (str);
}
