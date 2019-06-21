/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Functions to create map elements
*/

#include "map.h"

static const char const *bg_files[] = {
    "ressources/sky.png",
    "ressources/bg1.png",
    "ressources/bg2.png",
    "ressources/bg3.png",
    NULL
};

static const char const *dirt_file[] = {
    "ressources/empty.png",
    "ressources/dirt/dirt.png",
    "ressources/dirt/dirt_left.png",
    "ressources/dirt/dirt_right.png",
    "ressources/dirt/dirt_col.png",
    "ressources/dirt/dirt_down.png",
    "ressources/dirt/dirt_left_corner.png",
    "ressources/dirt/dirt_right_corner.png",
    "ressources/dirt/dirt_col_down.png",
    "ressources/dirt/grass_mid.png",
    "ressources/dirt/grass_left.png",
    "ressources/dirt/grass_right.png",
    "ressources/dirt/grass_col.png",
    "ressources/dirt/grass_cliff_mid.png",
    "ressources/dirt/grass_cliff_left.png",
    "ressources/dirt/grass_cliff_right.png",
    "ressources/dirt/grass.png"
};

int get_dirt_id(map_t const *map, char const *buffer, int x, int y)
{
    int id = 1;

    if (y > 0 && buffer[(y - 1) * map->width + x + y - 1] != '#'
    && buffer[(y - 1) * map->width + x + y - 1] != '~'
    && buffer[(y - 1) * map->width + x + y - 1] != 'B')
        id += 8;
    if (y < map->height - 1 && buffer[(y + 1) * map->width + x + y + 1] != '#'
    && buffer[(y + 1) * map->width + x + y + 1] != 'B')
        id += 4;
    if (x > 0 && buffer[y * map->width + x + y - 1] != '#'
    && buffer[y * map->width + x + y - 1] != 'B')
        id += 1;
    if (x < map->width - 1 && buffer[y * map->width + x + y + 1] != '#'
    && buffer[y * map->width + x + y + 1] != 'B')
        id += 2;
    return (id);
}

element_t *create_element(map_t *map, sfVector2f pos, int id)
{
    element_t *new_element = malloc(sizeof(element_t));

    if (!new_element)
        return (NULL);
    new_element->type = (id == SKY ? SKY : DIRT);
    new_element->texture = sfTexture_createFromFile(dirt_file[id], NULL);
    new_element->sprite = sfSprite_create();
    if (!new_element->texture || !new_element->sprite)
        return (NULL);
    sfSprite_setTexture(new_element->sprite, new_element->texture, sfTrue);
    sfSprite_setScale(new_element->sprite,
        (sfVector2f){map->scaling_factor, map->scaling_factor});
    sfSprite_setPosition(new_element->sprite, pos);
    return (new_element);
}

void create_backgrounds(map_t *map)
{
    for (map->nb[BG] = 0; bg_files[map->nb[BG]]; map->nb[BG]++);
    map->nb[BG] *= 2;
    map->bg = malloc(sizeof(element_t *) * map->nb[BG]);
    for (int i = 0; i < map->nb[BG]; i++) {
        map->bg[i] = malloc(sizeof(element_t));
        map->bg[i]->texture =
        sfTexture_createFromFile(bg_files[(i - i % 2) / 2], NULL);
        map->bg[i]->sprite = sfSprite_create();
        sfSprite_setTexture(map->bg[i]->sprite, map->bg[i]->texture, sfTrue);
        if (i % 2)
            sfSprite_setPosition(map->bg[i]->sprite, (sfVector2f){1920, 0});
    }
}
