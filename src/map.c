/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Function to control map
*/

#include "map.h"

void map_draw(sfRenderWindow *window, element_t *element)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(element->sprite);

    if (bounds.left < 1920 && bounds.left + bounds.width > 0)
        sfRenderWindow_drawSprite(window, element->sprite, NULL);
}

static void destroy_element(element_t *element)
{
    sfTexture_destroy(element->texture);
    sfSprite_destroy(element->sprite);
    free(element);
}

void map_destroy(map_t *map)
{
    for (int i = 0; i < map->nb[COINS]; i++)
        destroy_element(map->coins[i]);
    free(map->coins);
    for (int i = 0; i < map->nb[SPIKES]; i++)
        destroy_element(map->spikes[i]);
    free(map->spikes);
    for (int i = 0; i < map->nb[EYES]; i++)
        eye_destroy(map->eyes[i]);
    free(map->eyes);
    for (int i = 0; i < map->nb[BG]; i++)
        destroy_element(map->bg[i]);
    free(map->bg);
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++)
            destroy_element(map->el[y][x]);
        free(map->el[y]);
    }
    destroy_money_preview(&map->m_preview);
    free(map->el);
    free(map);
}
