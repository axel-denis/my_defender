/*
** EPITECH PROJECT, 2022
** My_Defender
** File description:
** pause_menu
*/
/*
button *create_buttons_pause(env_t *env)
{
    button *buttons = malloc(sizeof(button) * 6);

    buttons[0] = create_button(VC{.4, .4}, VC{460 + 200, 400 + 261}, sfFalse);
    buttons[1] = create_button(VC{-.4, .4}, VC{460 - 200, 400 + 261}, sfFalse);
    buttons[2] = create_button(VC{0.2, 0.2}, VC{258, 400 - 150}, sfTrue);
    buttons[3] = create_button(VC{0.2, 0.2}, VC{258, 400 + 450}, sfTrue);
    buttons[5] = create_button(VC{0.2, 0.2}, VC{258, 400 + 50}, sfTrue);
    buttons[4] = create_button(VC{0.2, 0.2}, VC{258, 400 + 250}, sfTrue);
    set_textures_options(buttons);
    if (env->langue[0] == 'F') {
        setup_button_text(&(buttons[2]), "Langue: ", "font/Xero.ttf", 30);
        setup_button_text(&(buttons[3]), "Retour", "font/Xero.ttf", 40);
    } else {
        setup_button_text(&(buttons[2]), "Language: ", "font/Xero.ttf", 30);
        setup_button_text(&(buttons[3]), "Return", "font/Xero.ttf", 40);
    }
    setup_button_text(&(buttons[4]), "Volume: ", "font/Xero.ttf", 30);
    setup_button_text(&(buttons[5]), "fps: ", "font/Xero.ttf", 30);
    for (int i = 0; i < 6; i++)
        setup_button_sounds(&(buttons[i]), "sounds/click.ogg", "sounds/hover.ogg", env);
    return (buttons);
}

void pause(sfRenderWindow *window, object mouse, int *keys, env_t *env)
{
    int open = 1;
    button *buttons = create_buttons_pause(env);
    text texte = setup_text("  Pause", "font/o_driftbold.ttf", 150);
    object backfr = create_object("img/options_fr.jpg", VC{0, 0}, VC{1, 1});
    object backen = create_object("img/options_en.jpg", VC{0, 0}, VC{1, 1});

    setup_buttons_options(buttons, env);
    sfText_setPosition(texte.text, VC{960 - 860, WINDOW_HEIGHT / 2 - 510});
    while (sfRenderWindow_isOpen(window) && open) {
        sfRenderWindow_clear(window, sfBlack);
        open = !get_events(window, keys)[sfKeyEscape];
        buttons_manager(buttons, window, keys, env);
        if (is_pressed(buttons[3], window, keys))
            open = 0;
        display_background(window, backfr, backen, env);
        sfRenderWindow_drawText(window, texte.text, NULL);
        display_options(window, mouse, buttons, keys);
        sfRenderWindow_display(window);
    }
    for (int i = 0; i < 6; i++)
        destroy_button(buttons[i]);
    keys[sfKeyEscape] = 0;
}
*/
