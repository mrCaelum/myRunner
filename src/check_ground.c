/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Check if player is on the ground
*/

#include "collitions.h"

static int check_ground_el(player_t *player, map_t *map, element_t *element)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(player->sprite);
    float mg = (float)(20 * map->scaling_factor);
    float bottom = bounds.top + bounds.height;
    float left = bounds.left;
    float right = bounds.left + bounds.width;

    if (element->type != DIRT)
        return (0);
    if ((is_point_in((sfVector2f){left, bottom}, element->sprite)
    && is_point_in((sfVector2f){left + mg, bottom}, element->sprite))
    || (is_point_in((sfVector2f){right, bottom}, element->sprite)
    && is_point_in((sfVector2f){right - mg, bottom}, element->sprite)))
        return (1);
    return (0);
}

int check_ground(player_t *player, map_t *map)
{
    int value = 0;

    for (int y = 0; y < map->height; y++)
        for (int x = 0; x < map->width; x++)
            value += check_ground_el(player, map, map->el[y][x]);
    return (value);
}
