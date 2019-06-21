/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Player functions
*/

#include "game.h"
#include "collitions.h"

static const char const *p_textures[] = {
    "ressources/player_l.png",
    "ressources/player_r.png",
    "ressources/run_l.png",
    "ressources/run_r.png",
    NULL
};

player_t *player_create(inventory_t *inv, sfVector2f const pos, float scale)
{
    player_t *player = malloc(sizeof(player_t));

    player->inventory = inv;
    for (int i = 0; p_textures[i]; i++)
        player->texture[i] =
        sfTexture_createFromFile(p_textures[i], NULL);
    player->sprite = sfSprite_create();
    if (!player->sprite)
        return (NULL);
    player->etat = 1;
    player->is_alive = 1;
    player->rect = (sfIntRect){0, 0, 160, 160};
    player->move = (sfVector2f){0, 0};
    player->init_pos = pos;
    sfSprite_setTexture(player->sprite, player->texture[1], sfTrue);
    sfSprite_setScale(player->sprite, (sfVector2f){scale, scale});
    sfSprite_setTextureRect(player->sprite, player->rect);
    sfSprite_setPosition(player->sprite, pos);
    return (player);
}

static void player_update_x(player_t *player, map_t *map)
{
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        player->move.x = -13 * map->scaling_factor;
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        player->move.x = 13 * map->scaling_factor;
    update_player_etat(player);
    if (check_collide(player, map, X_COLLIDE)) {
        player->move.x = 0;
        return;
    }
    if (player->move.x != 0) {
        map_move(map, player, (sfVector2f){player->move.x, 0});
        player->move.x = 0;
    }
}

static void player_update_y(player_t *player, map_t *map)
{
    if (sfKeyboard_isKeyPressed(sfKeyDown))
        player->move.y += 0.5 * map->scaling_factor;
    if (sfKeyboard_isKeyPressed(sfKeySpace) && check_ground(player, map)) {
        player->move.y = -20 * map->scaling_factor;
    }
    if (!check_collide(player, map, Y_COLLIDE)) {
        if (player->move.y != 0)
            sfSprite_move(player->sprite, (sfVector2f){0, player->move.y});
        player->move.y += 0.6 * map->scaling_factor;
    }
}

void player_update(player_t *player, map_t *map)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(player->sprite);
    sfFloatRect bounds2;

    if (bounds.top > map->opt.height)
        player->is_alive = 0;
    for (int i = 0; i < map->nb[SPIKES]; i++) {
        bounds2 = sfSprite_getGlobalBounds(map->spikes[i]->sprite);
        if (sfFloatRect_intersects(&bounds, &bounds2, NULL))
            player->is_alive = 0;
    }
    player_update_x(player, map);
    player_update_y(player, map);
}

void player_destroy(player_t *player)
{
    sfSprite_destroy(player->sprite);
    for (size_t i = 0; i < 2; i++)
        sfTexture_destroy(player->texture[i]);
    free(player);
}
