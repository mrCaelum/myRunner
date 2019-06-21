/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Player header
*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdlib.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "map.h"
#include "player.h"

typedef struct player player_t;
typedef struct graphical_element element_t;
typedef struct map map_t;
typedef struct inventory inventory_t;

#define IDLE 0
#define RUN 1
#define JUMP 2

struct inventory {
    unsigned int money;
};

struct player {
    inventory_t *inventory;
    int is_alive;
    int etat;
    sfTexture *texture[4];
    sfSprite *sprite;
    sfIntRect rect;
    sfVector2f pos;
    sfVector2f init_pos;
    sfVector2f move;
};

player_t *player_create(inventory_t *inv, sfVector2f const pos, float scale);
void player_jump(player_t *player);
void player_update(player_t *player, map_t *map);
void update_player_etat(player_t *player);
void player_destroy(player_t *player);

#endif
