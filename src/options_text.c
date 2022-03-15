/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** options_text c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "menu.h"
#include "button.h"

void set_button_screen_txt(button *buttons, env_t *env)
{
    char *screen = set_screen_txt(env);
    char *screen_txt;

    screen_txt = malloc(sizeof(char) * (8 + my_strlen(screen) + ENGLISH));
    if (ENGLISH)
        screen_txt = my_strcpy(screen_txt, "Screen: ");
    else
        screen_txt = my_strcpy(screen_txt, "Ecran: ");
    screen_txt = my_strcat(screen_txt, screen);
    sfText_setString(buttons->text.text, screen_txt);
    center_button_text(buttons);
    free(screen_txt);
    free(screen);
}

void set_button_volume_txt(button *buttons, env_t *env)
{
    char *volume = my_nbr_to_str(env->volume);
    char *volume_txt = malloc(sizeof(char) * (9 + my_strlen(volume)));

    volume_txt = my_strcpy(volume_txt, "Volume: ");
    volume_txt = my_strcat(volume_txt, volume);
    sfText_setString(buttons->text.text, volume_txt);
    center_button_text(buttons);
    free(volume_txt);
    free(volume);
}

void set_button_fps_txt(button *buttons, env_t *env)
{
    char *fps = my_nbr_to_str(env->fps);
    char *fps_txt = malloc(sizeof(char) * (6 + my_strlen(fps)));

    fps_txt = my_strcpy(fps_txt, "Fps: ");
    fps_txt = my_strcat(fps_txt, fps);
    sfText_setString(buttons->text.text, fps_txt);
    center_button_text(buttons);
    free(fps_txt);
    free(fps);
}

void set_button_resolution_txt(button *buttons, env_t *env)
{
    char *res1 = my_nbr_to_str(env->resolution);
    char *res2 = my_nbr_to_str(env->resolution / 16 * 9);
    int len = my_strlen(res1) + my_strlen(res2) + (env->langue[0] == 'F') * 2;
    char *resolution_txt = malloc(sizeof(char) * (8 + len));

    if (env->langue[0] == 'E')
        resolution_txt = my_strcpy(resolution_txt, "Size: ");
    else
        resolution_txt = my_strcpy(resolution_txt, "Taille: ");
    my_strcat(resolution_txt, res1);
    my_strcat(resolution_txt, "x");
    my_strcat(resolution_txt, res2);
    sfText_setString(buttons->text.text, resolution_txt);
    center_button_text(buttons);
    free(resolution_txt);
    free(res1);
    free(res2);
}

void set_button_vsync_txt(button *buttons, env_t *env)
{
    char *vsync;
    char *vsync_txt;

    if (env->langue[0] == 'E') {
        if (env->vsync == 0)
            vsync = my_strdup("Off");
        else
            vsync = my_strdup("On");
    } else {
        if (env->vsync == 0)
            vsync = my_strdup("Non");
        else
            vsync = my_strdup("Oui");
    }
    vsync_txt = malloc(sizeof(char *) * (7 + my_strlen(vsync)));
    vsync_txt = my_strcpy(vsync_txt, "Vsync: ");
    sfText_setString(buttons->text.text, my_strcat(vsync_txt, vsync));
    center_button_text(buttons);
    free(vsync);
    free(vsync_txt);
}
