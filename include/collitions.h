/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Collisions checker header file
*/

#ifndef COLLISIONS_H_
#define COLLISIONS_H_

#include "map.h"
#include "player.h"

#define X_COLLIDE 0
#define Y_COLLIDE 1

int is_point_in(sfVector2f const point, sfSprite const *sprite);
int check_ground(player_t *player, map_t *map);
int check_collide(player_t *player, map_t *map, int i);

#endif
