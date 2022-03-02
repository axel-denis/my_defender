/*
** EPITECH PROJECT, 2021
** my_putstr
** File description:
** affiche un string
*/

int my_strlen(char const *str);

void my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
}

void my_errorstr(char const *str)
{
    write(2, str, my_strlen(str));
}
