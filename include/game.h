/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Header for game.c
*/

#ifndef GAME_H_
#define GAME_H_

#include "map.h"
#include "player.h"

typedef struct player player_t;
typedef struct graphical_element element_t;
typedef struct map map_t;
typedef struct options options_t;
typedef struct inventory inventory_t;

options_t get_options(unsigned int *money);
void set_options(struct setting_button **button, int nb);
void update(sfClock *clock, map_t *map, player_t *player, inventory_t *inv);
void game_loop(sfRenderWindow *window, map_t *map, player_t *player,
    inventory_t *inventory);
void check_doors(sfRenderWindow *window, player_t *player, map_t *map,
    inventory_t *inv);

#endif
