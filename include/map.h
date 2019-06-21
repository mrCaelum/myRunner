/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Map header
*/

#ifndef MAP_H_
#define MAP_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "str.h"
#include "player.h"

#define MAX_MAP_SIZE 4096
#define B_SIZE 256

#define SKY 0
#define DIRT 1

#define COINS 0
#define SPIKES 1
#define EYES 2
#define DOORS 3
#define SBTN 4
#define BG 5

#define EYE 0
#define PUPIL 1
#define TEAR 2

typedef struct options options_t;
typedef struct player player_t;
typedef struct graphical_element element_t;
typedef struct map map_t;

struct options {
    unsigned int width;
    unsigned int height;
    sfWindowStyle fullscreen;
    unsigned int framerate;
    sfBool v_sync;
    unsigned int *money;
};

struct tab_map_element_id {
    char id;
    int type;
};

struct tab_map_entity_id {
    char id;
    int *ptr;
    void (*create)(map_t *map, int i, sfVector2i pos);
};

struct money_preview {
    sfTexture *texture;
    sfSprite *sprite;
    sfFont *font;
    sfText *text;
    unsigned int const *money;
};

struct graphical_element {
    int type;
    sfTexture *texture;
    sfSprite *sprite;
};

struct eye {
    int is_active;
    int is_tear_active;
    sfVector2f tear_vector;
    sfTexture *texture[3];
    sfSprite *sprite[3];
};

struct door {
    char *name;
    int is_active;
    sfTexture *texture;
    sfSprite *sprite;
};

struct setting_button {
    int is_active;
    unsigned int value;
    sfTexture *texture;
    sfSprite *sprite;
    sfFont *font;
    sfText *text;
    sfText *dvalue;
};

struct map {
    unsigned int running;
    options_t opt;
    sfVector2f init_pos;
    float scaling_factor;
    float block_size;
    element_t ***el;
    element_t **bg;
    element_t **coins;
    element_t **spikes;
    struct eye **eyes;
    struct door **doors;
    struct setting_button **buttons;
    struct money_preview m_preview;
    int width;
    int height;
    int nb[5];
};

map_t *map_reader(char const *file, options_t opt);
int fill_map(map_t *map, char *buffer);
int check_map_char(char c);
void map_draw(sfRenderWindow *window, element_t *element);
void map_move(map_t *map, player_t *player, sfVector2f const vector);

void create_backgrounds(map_t *map);
element_t *create_element(map_t *map, sfVector2f pos, int id);
int get_dirt_id(map_t const *map, char const *buffer, int x, int y);

struct money_preview create_money_preview(unsigned int const *money);
void update_money_preview(struct money_preview *m_preview);
void destroy_money_preview(struct money_preview *m_preview);

void create_coin(map_t *map, int i, sfVector2i pos);
void create_spike(map_t *map, int i, sfVector2i pos);
void create_eye(map_t *map, int i, sfVector2i pos);
void create_door(map_t *map, int i, sfVector2i pos);
void create_button(map_t *map, int i, sfVector2i pos);
sfText *create_text(sfFont *font, char const *str, sfVector2f pos, int size);

void update_buttons(map_t *map, player_t *player);

int is_point_in(sfVector2f const point, sfSprite const *sprite);

void eyes_update(map_t *map, player_t *player);
void eye_destroy(struct eye *eye);

void map_destroy(map_t *map);

#endif
