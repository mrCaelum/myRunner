/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Main function
*/

#include "game.h"

static inventory_t *init_inventory(void)
{
    inventory_t *inventory = malloc(sizeof(inventory_t));

    inventory->money = 0;
    return (inventory);
}

static sfRenderWindow *init_window(options_t opt)
{
    sfRenderWindow *window = sfRenderWindow_create((sfVideoMode)
    {opt.width, opt.height, 32}, "my_runner",
    sfTitlebar | sfClose | opt.fullscreen, NULL);

    if (!window)
        return (NULL);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    sfRenderWindow_setFramerateLimit(window, opt.framerate);
    sfRenderWindow_setVerticalSyncEnabled(window, opt.v_sync);
    return (window);
}

static sfMusic *init_music(void)
{
    sfMusic *music = sfMusic_createFromFile("ressources/music.ogg");

    if (!music)
        return (NULL);
    sfMusic_play(music);
    sfMusic_setLoop(music, sfTrue);
    return (music);
}

static void print_help(sfRenderWindow *window)
{
    sfTexture *texture = sfTexture_createFromFile("ressources/help.png", NULL);
    sfSprite *sprite = sfSprite_create();

    if (!texture || !sprite)
        return;
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_display(window);
    while (!sfKeyboard_isKeyPressed(sfKeyEscape));
    while (sfKeyboard_isKeyPressed(sfKeyEscape));
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
}

int main(int argc, char const *argv[])
{
    inventory_t *inventory = init_inventory();
    options_t opt = get_options(&inventory->money);
    sfRenderWindow *window = init_window(opt);
    map_t *map = map_reader(argc > 1 && !str_is_equal(argv[1], "-h") ?
    argv[1] : "maps/menu.map", opt);
    player_t *player = !map ? NULL :
    player_create(inventory, (sfVector2f){0, 0}, map->scaling_factor);
    sfMusic *music = init_music();

    if (!map || !player || !window || !music)
        return (84);
    if (argc > 1 && str_is_equal(argv[1], "-h"))
        print_help(window);
    game_loop(window, map, player, inventory);
    map_destroy(map);
    player_destroy(player);
    sfMusic_destroy(music);
    return (0);
}
