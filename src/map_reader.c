/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** map_reader.c
*/

#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"

#define REAL_MAP_LEN 192
#define MAP_LEN 32

sfSprite *create_sprite(game_data *data, int type, int x, int y)
{
    sfSprite *sprite = sfSprite_create();

    sfSprite_setTexture(sprite, data->ground_texture, sfFalse);
    sfSprite_setPosition(sprite, (sfVector2f) {x, y})
}

int setup_map_block(game_data *data, map_block *line, char *buffer)
{
    char *temp_str = NULL;

    if (strlen(buffer) < 3 || buffer[0] - '0' < 0 || buffer[0] - '0' > 1)
        return 1;
    line->type = buffer[0] - '0';

    if (line->type = 1) {
        temp_str = max_strdup(buffer[1], 2);
        line->next_path.x = my_get_nbr(temp_str);
        free(temp_str);
        temp_str = max_strdup(buffer[3], 2);
        line->next_path.y = my_get_nbr(temp_str);
        free(temp_str);
    }
    line->turret = NULL;
    line->sprite = create_sprite(data, line->type)
    return 0;
}

map_block *map_line(game_data *data, char *buffer)
{
    map_block *line = malloc(sizeof(map_block) * (MAP_LEN));

    if (my_strlen(buffer) != REAL_MAP_LEN)
        return NULL;

    for (int i = 0; i < REAL_MAP_LEN; i++) {
        if (buffer[i] == '0')

    }
}

map_block **read_map(env *game, char *path)
{
    FILE *fd = fopen(path, "r");
    size_t size = 0;
    char *buffer = NULL;
    map_block **final_tab = malloc(sizeof(map_block *) * 19);

    final_tab[18] = NULL;
    if (fd == NULL)
        return NULL;
    for (int i = 0; i < 18; i++) {
        size = getline(&buffer, &size, fd);
        if (size < 0) {
            free(buffer);
            return NULL;
        }
        final_tab[i] = map_line(buffer);
        if (final_tab[i] == NULL)
            return NULL;
    }
    return final_tab;
}
