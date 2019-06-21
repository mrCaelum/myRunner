/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Eyes mob update functions
*/

#include <math.h>
#include "map.h"
#include "player.h"

static int sprites_intersect(player_t *player, map_t *map, sfSprite *tear)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(player->sprite);
    sfFloatRect bounds2 = sfSprite_getGlobalBounds(tear);

    if (sfFloatRect_intersects(&bounds, &bounds2, NULL)) {
        player->is_alive = 0;
        return (1);
    } else if (bounds2.top + bounds2.height < -10 || bounds2.top > 1090
    || bounds2.left + bounds2.width < -10 || bounds2.left > 1930)
        return (1);
    for (int y = 0, x = 0; y < map->height; x++) {
        bounds = x < map->width ?
        sfSprite_getGlobalBounds(map->el[y][x]->sprite) : bounds;
        if (x >= map->width) {
            x = 0;
            y++;
        } else if (map->el[y][x]->type == DIRT
        && sfFloatRect_intersects(&bounds, &bounds2, NULL))
            return (1);
    }
    return (0);
}

static sfVector2f get_center(sfSprite *sprite1, sfSprite *sprite2)
{
    sfFloatRect bounds1 = sfSprite_getGlobalBounds(sprite1);
    sfFloatRect bounds2 = sfSprite_getGlobalBounds(sprite2);

    return ((sfVector2f)
    {bounds1.left + (bounds1.width / 2) - (bounds2.width / 2),
    bounds1.top + (bounds1.height / 2) - (bounds2.height / 2)});
}

static void tear_update(map_t *map, player_t *player, struct eye *eye,
    sfVector2f const *vector)
{
    if (eye->is_active && !eye->is_tear_active) {
        eye->is_tear_active = 1;
        eye->tear_vector = vector[2];
        sfSprite_setPosition(eye->sprite[TEAR], vector[1]);
    } else if (eye->is_tear_active) {
        sfSprite_move(eye->sprite[TEAR], eye->tear_vector);
    }
    if (sprites_intersect(player, map, eye->sprite[TEAR]))
        eye->is_tear_active = 0;
}

void eyes_update(map_t *map, player_t *player)
{
    sfFloatRect pbnds = sfSprite_getGlobalBounds(player->sprite);
    sfVector2f p_pos = (sfVector2f)
    {pbnds.left + pbnds.width / 2, pbnds.top + pbnds.height / 2};
    sfVector2f vector[3];
    float hypotenuse;

    for (int i = 0; i < map->nb[EYES]; i++) {
        vector[1] =
        get_center(map->eyes[i]->sprite[0], map->eyes[i]->sprite[1]);
        vector[0] = (sfVector2f){vector[1].x - p_pos.x, vector[1].y - p_pos.y};
        hypotenuse =
        sqrt(vector[0].x * vector[0].x + vector[0].y * vector[0].y);
        map->eyes[i]->is_active = hypotenuse < 2600 * map->scaling_factor;
        vector[2].x = -(vector[0].x / hypotenuse) * 11 * map->scaling_factor;
        vector[2].y = -(vector[0].y / hypotenuse) * 11 * map->scaling_factor;
        sfSprite_setPosition(map->eyes[i]->sprite[PUPIL], (sfVector2f)
        {vector[1].x + vector[2].x, vector[1].y + vector[2].y});
        tear_update(map, player, map->eyes[i], vector);
    }
}

void eye_destroy(struct eye *eye)
{
    for (int i = 0; i < 3; i++) {
        sfSprite_destroy(eye->sprite[i]);
        sfTexture_destroy(eye->texture[i]);
    }
    free(eye);
}
