/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Main game file
*/

#include "game.h"

static void events(sfRenderWindow *window, sfEvent event)
{
    if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(window);
}

static void draw_entities(sfRenderWindow *window, map_t *map)
{
    for (int i = 0; i < map->nb[COINS]; i++)
        if (map->coins[i]->type == 1)
            sfRenderWindow_drawSprite(window, map->coins[i]->sprite, NULL);
    for (int i = 0; i < map->nb[SPIKES]; i++)
        sfRenderWindow_drawSprite(window, map->spikes[i]->sprite, NULL);
    for (int i = 0; i < map->nb[EYES]; i++) {
        for (int j = 0; j < 2; j++)
            sfRenderWindow_drawSprite(window, map->eyes[i]->sprite[j], NULL);
        if (map->eyes[i]->is_tear_active)
            sfRenderWindow_drawSprite(window, map->eyes[i]->sprite[2], NULL);
    }
}

static void draw_map(sfRenderWindow *window, map_t *map)
{
    for (int i = 0; i < map->nb[BG]; i++)
        sfRenderWindow_drawSprite(window, map->bg[i]->sprite, NULL);
    for (int y = 0; y < map->height; y++)
        for (int x = 0; x < map->width; x++)
            map_draw(window, map->el[y][x]);
    for (int i = 0; i < map->nb[DOORS]; i++)
        sfRenderWindow_drawSprite(window, map->doors[i]->sprite, NULL);
    for (int i = 0; i < map->nb[SBTN]; i++) {
        sfRenderWindow_drawSprite(window, map->buttons[i]->sprite, NULL);
        sfRenderWindow_drawText(window, map->buttons[i]->text, NULL);
        sfRenderWindow_drawText(window, map->buttons[i]->dvalue, NULL);
    }
}

static void draw(sfRenderWindow *window, map_t *map, player_t *player)
{
    sfRenderWindow_clear(window, sfWhite);
    draw_map(window, map);
    draw_entities(window, map);
    sfRenderWindow_drawSprite(window, player->sprite, NULL);
    sfRenderWindow_drawSprite(window, map->m_preview.sprite, NULL);
    sfRenderWindow_drawText(window, map->m_preview.text, NULL);
    sfRenderWindow_display(window);
}

void game_loop(sfRenderWindow *window, map_t *map, player_t *player,
    inventory_t *inventory)
{
    sfClock *clock = sfClock_create();
    sfEvent event;

    sfSprite_setPosition(player->sprite, map->init_pos);
    while (map->running) {
        while (sfRenderWindow_pollEvent(window, &event))
            events(window, event);
        check_doors(window, player, map, inventory);
        update(clock, map, player, inventory);
        draw(window, map, player);
        if (!sfRenderWindow_isOpen(window) || !player->is_alive)
            break;
    }
    if (map->nb[SBTN] > 0)
        set_options(map->buttons, map->nb[SBTN]);
    player->is_alive = 1;
    sfClock_destroy(clock);
}
