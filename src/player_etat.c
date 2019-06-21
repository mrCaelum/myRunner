/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Player etat update
*/

#include "game.h"

static void change(player_t *player, sfIntRect rect)
{
    player->rect = rect;
    sfSprite_setTexture(player->sprite, player->texture[player->etat], sfTrue);
    sfSprite_setTextureRect(player->sprite, player->rect);
}

void update_player_etat(player_t *player)
{
    if (player->etat != 2 && player->move.x > 0) {
        player->etat = 2;
        change(player, (sfIntRect){0, 0, 198, 156});
    } else if (player->etat != 3 && player->move.x < 0) {
        player->etat = 3;
        change(player, (sfIntRect){0, 0, 198, 156});
    } else if (player->etat > 1 && !player->move.x) {
        player->etat -= 2;
        change(player, (sfIntRect){0, 0, 160, 160});
    }
}
