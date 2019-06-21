/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Function to fill the map with th map reader function
*/

#include "game.h"

static const struct tab_map_element_id const tab[] = {
    {' ', SKY},
    {'P', SKY},
    {'.', SKY},
    {'~', SKY},
    {'o', SKY},
    {'D', SKY},
    {'B', DIRT},
    {'_', DIRT},
    {'#', DIRT},
    {0, 0}
};

static struct tab_map_entity_id tab_enty[] = {
    {'.', NULL, &create_coin},
    {'~', NULL, &create_spike},
    {'o', NULL, &create_eye},
    {'D', NULL, &create_door},
    {'B', NULL, &create_button},
    {0, NULL}
};

static int map_tab_check(map_t *map, sfVector2i pos, int *id, char *buffer)
{
    map->el[pos.y][pos.x] = malloc(map->width * sizeof(element_t));
    map->el[pos.y][pos.x]->sprite = NULL;
    for (int i = 0; tab[i].id; i++) {
        if (buffer[pos.y * map->width + pos.x + pos.y] == 'P')
            map->init_pos = (sfVector2f){pos.x * B_SIZE * map->scaling_factor,
            pos.y * B_SIZE * map->scaling_factor};
        if (tab[i].id == buffer[pos.y * map->width + pos.x + pos.y])
            map->el[pos.y][pos.x] = create_element(map,
                (sfVector2f){pos.x * B_SIZE * map->scaling_factor,
                pos.y * B_SIZE * map->scaling_factor}, tab[i].type == DIRT ?
                get_dirt_id(map, buffer, pos.x, pos.y) : tab[i].type);
    }
    for (int i = 0; tab_enty[i].id; i++)
        if (buffer[pos.y * map->width + pos.x + pos.y] == tab_enty[i].id) {
            tab_enty[i].create(map, id[i], pos);
            id[i]++;
        }
    if (!map->el[pos.y][pos.x])
        return (1);
    return (0);
}

static void alloc_map_elements(map_t *map)
{
    map->el = malloc(map->height * sizeof(element_t **));
    map->coins = malloc(map->nb[COINS] * sizeof(element_t *));
    map->spikes = malloc(map->nb[SPIKES] * sizeof(element_t *));
    map->eyes = malloc(map->nb[EYES] * sizeof(struct eye *));
    map->doors = malloc(map->nb[DOORS] * sizeof(struct door *));
    map->buttons = malloc(map->nb[SBTN] * sizeof(struct setting_button *));
}

int fill_map(map_t *map, char *buffer)
{
    int errors = 0;
    int id[5] = {0, 0, 0, 0, 0};

    create_backgrounds(map);
    alloc_map_elements(map);
    if (!map->el || !map->coins || !map->spikes || !map->eyes || !map->doors)
        return (1);
    for (int y = 0; y < map->height; y++) {
        map->el[y] = malloc(map->width * sizeof(element_t *));
        for (int x = 0; x < map->width; x++)
            errors += map_tab_check(map, (sfVector2i){x, y}, id, buffer);
    }
    for (int i = 0; i < 5; i++)
        if (id[i] != map->nb[i])
            errors++;
    return (errors);
}

int check_map_char(char c)
{
    if (c == '\n')
        return (1);
    for (int i = 0; tab[i].id; i++)
        if (c == tab[i].id)
            return (1);
    return (0);
}
