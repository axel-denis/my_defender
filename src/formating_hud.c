/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** formating_hud.c
*/

#include "menu.h"
#include "enemy.h"
#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"
#include "maths.h"
#include "map.h"
#include "hud.h"

char *formating_hud_in(int value)
{
    char *text_val = my_dec_to_base(value / 10, "0123456789");
    char *text_abs = my_dec_to_base(ABS(value % 10), "0123456789");
    int len =  + my_strlen(text_val);
    char *texte = malloc(sizeof(char) * (4 + my_strlen(text_abs) + len));

    texte = my_strcpy(texte, text_val);
    my_strcat(texte, ".");
    my_strcat(texte, text_abs);
    my_strcat(texte, "/s");
    free(text_val);
    free(text_abs);
    return (texte);
}

char *formating_hud(int value)
{
    char *text_val = my_dec_to_base(value / 10, "0123456789");
    char *text_abs = my_dec_to_base(ABS(value % 10), "0123456789");
    int len =  + my_strlen(text_val);
    char *texte = malloc(sizeof(char) * (2 + my_strlen(text_abs) + len));

    texte = my_strcpy(texte, text_val);
    my_strcat(texte, ".");
    my_strcat(texte, text_abs);
    free(text_val);
    free(text_abs);
    return (texte);
}
