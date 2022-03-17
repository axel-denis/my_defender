/*
** EPITECH PROJECT, 2021
** myrunner
** File description:
** lib.h
*/

#ifndef LIB_H
    #define LIB_H

    #define ABS(x) ((x < 0) ? -x : x)

char *my_revstr(char *str);
char *my_dec_to_base(long nb, char *base);
int my_strlen(char const *str);
int my_get_nbr(char *str);
void my_put_nbr(int nb);
void my_putchar(char c);
void my_putstr(char const *str);
char *my_nbr_to_str(int nb);
int lines_count(char *str, char separator);
int line_len(char *str, char endline);
char **my_split(char *str, char separator);
char *fill_text(char const *text);
char *dec_to_base(unsigned int dec, int base, int maj);
int my_char_isalpha(char const letter);
int my_str_isalpha(char const *str);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char *str);
char *max_strdup(char *str, int max);
char *my_strcat(char *dest , char *src);
void my_errorstr(char const *str);

#endif
