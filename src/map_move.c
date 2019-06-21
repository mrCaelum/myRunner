/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Map move
*/

#include "game.h"

static int move_borders(map_t *map, player_t *player, sfVector2f const vector)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(player->sprite);

    if ((bounds.left < map->opt.width / 3
    || bounds.left > map->opt.width / 3 + map->block_size)
    && (vector.x > 0 && bounds.left >= 0
    || vector.x < 0 && bounds.left + bounds.width <= map->opt.width)) {
        sfSprite_move(player->sprite,(sfVector2f){-vector.x, -vector.y});
        return (1);
    }
    if (sfSprite_getPosition(map->el[0][0]->sprite).x + vector.x > 0
    || sfSprite_getPosition(map->el[0][map->width - 1]->sprite).x + vector.x
    < 1920 - map->block_size) {
        if (bounds.left >= 0 && bounds.left + bounds.width <= map->opt.width)
            sfSprite_move(player->sprite, (sfVector2f){-vector.x, -vector.y});
        return (1);
    }
    return (0);
}

static void move_elems(map_t *map, player_t *player, sfVector2f const vector)
{
    for (int i = 0; i < map->nb[COINS]; i++)
        sfSprite_move(map->coins[i]->sprite, vector);
    for (int i = 0; i < map->nb[SPIKES]; i++)
        sfSprite_move(map->spikes[i]->sprite, vector);
    for (int i = 0; i < map->nb[EYES]; i++)
        for (int j = 0; j < 3; j++)
            sfSprite_move(map->eyes[i]->sprite[j], vector);
    for (int i = 0; i < map->nb[DOORS]; i++)
        sfSprite_move(map->doors[i]->sprite, vector);
    for (int y = 0; y < map->height; y++)
        for (size_t x = 0; x < map->width; x++)
            sfSprite_move(map->el[y][x]->sprite, vector);
    for (int i = 0; i < map->nb[SBTN]; i++) {
        sfSprite_move(map->buttons[i]->sprite, vector);
        sfText_move(map->buttons[i]->text, vector);
        sfText_move(map->buttons[i]->dvalue, vector);
    }
}

void map_move(map_t *map, player_t *player, sfVector2f const vector)
{
    if (move_borders(map, player, vector))
        return;
    for (int i = 0; i < 8; i++) {
        sfSprite_move(map->bg[i]->sprite,
            (sfVector2f){vector.x * (i - i % 2) / 18, 0});
        if (sfSprite_getPosition(map->bg[i]->sprite).x <= -map->opt.width)
            sfSprite_move(map->bg[i]->sprite,
                (sfVector2f){map->opt.width * 2, 0});
        if (sfSprite_getPosition(map->bg[i]->sprite).x >= map->opt.width)
            sfSprite_move(map->bg[i]->sprite,
                (sfVector2f){-(int)(map->opt.width * 2), 0});
    }
    move_elems(map, player, vector);
}
