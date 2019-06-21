/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Collitions checker
*/

#include "collitions.h"

int is_point_in(sfVector2f const point, sfSprite const *sprite)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(sprite);

    if (point.x > bounds.left && point.x < bounds.left + bounds.width
    && point.y > bounds.top && point.y < bounds.top + bounds.height)
        return (1);
    return (0);
}

static int is_x_collide(player_t *player, map_t *map, element_t *element)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(player->sprite);
    float mg = (float)(20 * map->scaling_factor);
    float top = bounds.top;
    float bottom = bounds.top + bounds.height;
    float left = bounds.left;
    float right = bounds.left + bounds.width;

    if (player->move.x > 0
    && ((is_point_in((sfVector2f){left, top}, element->sprite)
    && is_point_in((sfVector2f){left, top + mg}, element->sprite))
    || (is_point_in((sfVector2f){left, bottom}, element->sprite)
    && is_point_in((sfVector2f){left, bottom - mg * 2}, element->sprite)))
    || player->move.x < 0
    && ((is_point_in((sfVector2f){right, top}, element->sprite)
    && is_point_in((sfVector2f){right, top + mg}, element->sprite))
    || (is_point_in((sfVector2f){right, bottom}, element->sprite)
    && is_point_in((sfVector2f){right, bottom - mg * 2}, element->sprite))))
        return (1);
    return (0);
}

static int is_y_collide(player_t *player, map_t *map, element_t *element)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(player->sprite);
    float mg = (float)(20 * map->scaling_factor);
    float top = bounds.top;
    float bottom = bounds.top + bounds.height;
    float left = bounds.left;
    float right = bounds.left + bounds.width;

    if (player->move.y < 0
    && ((is_point_in((sfVector2f){left, top}, element->sprite)
    && is_point_in((sfVector2f){left + mg, top}, element->sprite))
    || (is_point_in((sfVector2f){right, top}, element->sprite)
    && is_point_in((sfVector2f){right - mg, top}, element->sprite)))
    || player->move.y > 0
    && ((is_point_in((sfVector2f){left, bottom}, element->sprite)
    && is_point_in((sfVector2f){left + mg, bottom}, element->sprite))
    || (is_point_in((sfVector2f){right, bottom}, element->sprite)
    && is_point_in((sfVector2f){right - mg, bottom}, element->sprite))))
        return (1);
    return (0);
}

static int is_collide(player_t *player, map_t *map, element_t *element, int i)
{
    if (element->type != DIRT)
        return (0);
    if (i == X_COLLIDE)
        return (is_x_collide(player, map, element));
    if (i == Y_COLLIDE)
        if (is_y_collide(player, map, element)) {
            player->move.y = 0;
            return (1);
        } else
            return (0);
    return (1);
}

int check_collide(player_t *player, map_t *map, int i)
{
    int collisions = 0;

    for (int y = 0; y < map->height; y++)
        for (int x = 0; x < map->width; x++)
            collisions += is_collide(player, map, map->el[y][x], i);
    return (collisions);
}
