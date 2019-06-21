/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Doors functions
*/

#include "game.h"

static map_t *start_rec(player_t *player, map_t *map, sfFloatRect p_bounds,
    int i)
{
    sfFloatRect d_bounds = sfSprite_getGlobalBounds(map->doors[i]->sprite);

    if (!sfKeyboard_isKeyPressed(sfKeyUp))
        map->doors[i]->is_active = 1;
    if (!player->move.x && !player->move.y
    && map->doors[i]->is_active
    && sfKeyboard_isKeyPressed(sfKeyUp)
    && sfFloatRect_intersects(&p_bounds, &d_bounds, NULL)) {
        if (str_is_equal(map->doors[i]->name, "exit"))
            map->running = 0;
        else {
            map->doors[i]->is_active = 0;
            return (map_reader(map->doors[i]->name, map->opt));
        }
    }
    return (NULL);
}

void check_doors(sfRenderWindow *window, player_t *player, map_t *map,
    inventory_t *inv)
{
    map_t *new = NULL;
    sfFloatRect p_bounds = sfSprite_getGlobalBounds(player->sprite);

    for (int i = 0; i < map->nb[DOORS]; i++) {
        new = start_rec(player, map, p_bounds, i);
        if (new) {
            map->init_pos = sfSprite_getPosition(player->sprite);
            game_loop(window, new, player, inv);
            sfSprite_setPosition(player->sprite, map->init_pos);
            map_destroy(new);
            new = NULL;
        }
    }
}
