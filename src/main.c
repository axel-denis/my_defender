/*
** EPITECH PROJECT, 2021
** mydefender
** File description:
** main.c
*/

#include "menu.h"
#include "enemy.h"
#include "csfml.h"
#include "lib.h"
#include "structs.h"
#include "mouse.h"
#include "button.h"
#include "events.h"
#include "map.h"

turret create_turret_1()
{
    turret template;

    template.type = 1;
    template.sprite = sfSprite_create();
    template.texture = sfTexture_createFromFile("", NULL);
    sfSprite_setTexture(template.sprite, template.texture, NULL);
}

void game(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    float money = 10000;
    float electricity = 0;
    float steel = 0;
    object background = create_object("img/background.jpg", VC{0, 0}, VC{1, 1});
    object worm_hole = create_object("img/icon.png", VC{env->starting_square.x * 60 , env->starting_square.y * 60 - 58}, VC{.3, 1});
    object epsilon = create_object("img/Epsilon.png", VC{1370, 35}, VC{.1, .1});
    object stats = create_object("img/blue_display.png", VC{1285, 5}, VC{1, 1});
    object cadre = create_object("img/temp.png", VC{0, 836 - 20}, VC{1, 0.6});
    enemy mob = create_enemy_type_1(env);
    turret tourelle = create_turret_1();
    text money_text = setup_text(my_nbr_to_str(money) , "font/oceanicdrift.ttf", 45);
    object button1 = create_object("img/Blue_button.png", VC{50, 836 - 20}, VC{0.3, 0.3});
    object button2 = create_object("img/Blue_button.png", VC{50, 836 - 20}, VC{0.3, 0.3});

    sfText_setPosition(money_text.text, VC{1430, 24});
    setmap_opacity(env);
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        sfRenderWindow_drawSprite(window, background.sprite, NULL);
        display_map(env, window);
        sfRenderWindow_drawSprite(window, stats.sprite, NULL);
        sfRenderWindow_drawSprite(window, epsilon.sprite, NULL);
        sfRenderWindow_drawText(window, money_text.text, NULL);
        sfRenderWindow_drawSprite(window, button1.sprite, NULL);
        sfRenderWindow_drawSprite(window, button2.sprite, NULL);
        sfRenderWindow_drawSprite(window, cadre.sprite, NULL);
        sfRenderWindow_drawSprite(window, worm_hole.sprite, NULL);
        sfRenderWindow_drawSprite(window, mob.sprite, NULL);
        update_mouse_cursor(window, mouse);
        sfRenderWindow_display(window);
        evolve_enemy(env, &mob);
    }
    keys[sfKeyEscape] = 0;
}

env_t *create_env(void)
{
    env_t *env = malloc(sizeof(env_t));

    env->data.music = sfMusic_createFromFile("sounds/uncharted-worlds.ogg");
    sfMusic_play(env->data.music);
    sfMusic_setLoop(env->data.music, sfTrue);
    sfMusic_setVolume(env->data.music, 60);
    env->volume = 100;
    env->langue = my_strdup("EN");
    env->data.ground_texture =
        sfTexture_createFromFile("img/grass.png", NULL);
    env->data.path_texture = sfTexture_createFromFile("img/dirt.png", NULL);
    env->player_stats.score = 0;
    return env;
}

int main(void)
{
    int *keys = init_keys();
    sfVideoMode main_w = {1920, 1080, 64};
    sfRenderWindow *window;
    object mouse = setup_mouse("img/cursor.png", VC{0.05, 0.05});
    env_t *env = create_env();

    window = sfRenderWindow_create(main_w, "My defender", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 75);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    if (read_map(env, "map") == 1) {
        my_errorstr("Error on map\n");
        return 84;
    }
    main_menu(window, mouse, keys, env);
    sfMusic_destroy(env->data.music);
    destroy_object(mouse);
    return (0);
}
