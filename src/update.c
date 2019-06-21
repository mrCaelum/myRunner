/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Update function
*/

#include "game.h"
#include "collitions.h"

static void anim(map_t *map, player_t *player)
{
    sfIntRect rect;

    player->rect.left = player->rect.left >= (player->etat < 2 ? 1760 : 3366) ?
    0 : player->rect.left + (player->etat < 2 ? 160 : 198);
    sfSprite_setTextureRect(player->sprite, player->rect);
    for (int i = 0; i < map->nb[COINS]; i++) {
        rect = sfSprite_getTextureRect(map->coins[i]->sprite);
        rect.left = rect.left >= 15 * 64 ? 0 : rect.left + 64;
        sfSprite_setTextureRect(map->coins[i]->sprite, rect);
    }
}

static void intersects(map_t *map, player_t *player, inventory_t *inv)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(player->sprite);
    sfFloatRect bounds2;

    for (int i = 0; i < map->nb[COINS]; i++) {
        bounds2 = sfSprite_getGlobalBounds(map->coins[i]->sprite);
        if (sfFloatRect_intersects(&bounds, &bounds2, NULL)
        && map->coins[i]->type != 0) {
            inv->money++;
            map->coins[i]->type = 0;
        }
    }
    for (int i = 0; i < map->nb[EYES]; i++) {
        bounds2 = sfSprite_getGlobalBounds(map->eyes[i]->sprite[EYE]);
        if (sfFloatRect_intersects(&bounds, &bounds2, NULL))
            player->is_alive = 0;
    }
}

void update(sfClock *clock, map_t *map, player_t *player, inventory_t *inv)
{
    static int i = 0;

    if (sfTime_asMilliseconds(sfClock_getElapsedTime(clock)) > 5) {
        i++;
        if (i >= 3) {
            anim(map, player);
            update_money_preview(&map->m_preview);
            i = 0;
        }
        update_buttons(map, player);
        intersects(map, player, inv);
        eyes_update(map, player);
        player_update(player, map);
        sfClock_restart(clock);
    }
}
