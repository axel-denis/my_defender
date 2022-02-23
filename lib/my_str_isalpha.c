/*
** EPITECH PROJECT, 2021
** my_str_isalpha
** File description:
** return 1 if the str only contain letters
*/

int my_char_isalpha(char const letter)
{
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
        return 0;
    return 1;
}

int my_str_isalpha(char const *str)
{
    if (str[0] == '\0') {
        return (1);
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (!my_char_isalpha(str[i]))
            return (0);
    }
    return (1);
}
