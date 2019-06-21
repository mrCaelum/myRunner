/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Functions to create map's entities
*/

#include "map.h"

static const char const *eye_files[] = {
    "ressources/eye.png",
    "ressources/pupil.png",
    "ressources/tear.png"
};

static const char const *doors_name[] = {
    "exit",
    "maps/settings.map",
    "maps/$.map",
    NULL
};

static const char const *button_name[] = {
    "Screen resolution",
    "Fullscreen",
    "FPS",
    "V_sync",
    NULL
};

static const char const *dval[] = {
    "1920x1080",
    "ON",
    "60",
    "ON",
    NULL
};

void create_coin(map_t *map, int i, sfVector2i pos)
{
    map->coins[i] = malloc(sizeof(element_t));
    map->coins[i]->type = 1;
    map->coins[i]->texture =
    sfTexture_createFromFile("ressources/coin.png", NULL);
    map->coins[i]->sprite = sfSprite_create();
    sfSprite_setTexture(map->coins[i]->sprite, map->coins[i]->texture, sfTrue);
    sfSprite_setPosition(map->coins[i]->sprite, (sfVector2f)
    {pos.x * B_SIZE * map->scaling_factor + B_SIZE / 2 * map->scaling_factor,
    pos.y * B_SIZE * map->scaling_factor + B_SIZE / 2 * map->scaling_factor});
    sfSprite_scale(map->coins[i]->sprite,
        (sfVector2f){map->scaling_factor, map->scaling_factor});
    sfSprite_setTextureRect(map->coins[i]->sprite, (sfIntRect){0, 0, 64, 64});
}

void create_spike(map_t *map, int i, sfVector2i pos)
{
    map->spikes[i] = malloc(sizeof(element_t));
    map->spikes[i]->type = 0;
    map->spikes[i]->texture =
    sfTexture_createFromFile("ressources/spikes.png", NULL);
    map->spikes[i]->sprite = sfSprite_create();
    sfSprite_setTexture(map->spikes[i]->sprite,
        map->spikes[i]->texture, sfTrue);
    sfSprite_setPosition(map->spikes[i]->sprite, (sfVector2f)
    {pos.x * B_SIZE * map->scaling_factor,
    pos.y * B_SIZE * map->scaling_factor + 192 * map->scaling_factor});
    sfSprite_scale(map->spikes[i]->sprite,
        (sfVector2f){map->scaling_factor, map->scaling_factor});
}

void create_eye(map_t *map, int i, sfVector2i pos)
{
    map->eyes[i] = malloc(sizeof(struct eye));
    for (int j = 0; j < 3; j++) {
        map->eyes[i]->texture[j] = sfTexture_createFromFile(eye_files[j], NULL);
        map->eyes[i]->sprite[j] = sfSprite_create();
        sfSprite_setTexture(map->eyes[i]->sprite[j],
            map->eyes[i]->texture[j], sfTrue);
        sfSprite_scale(map->eyes[i]->sprite[j],
            (sfVector2f){map->scaling_factor, map->scaling_factor});
        sfSprite_setPosition(map->eyes[i]->sprite[j], (sfVector2f)
        {(pos.x + 0.3) * map->block_size, (pos.y + 0.3) * map->block_size});
    }
    map->eyes[i]->is_active = 0;
    map->eyes[i]->is_tear_active = 0;
}

void create_door(map_t *map, int i, sfVector2i pos)
{
    char *tmp;

    map->doors[i] = malloc(sizeof(struct door));
    map->doors[i]->texture =
    sfTexture_createFromFile("ressources/door.png", NULL);
    map->doors[i]->sprite = sfSprite_create();
    sfSprite_setTexture(map->doors[i]->sprite, map->doors[i]->texture, sfTrue);
    sfSprite_scale(map->doors[i]->sprite,
        (sfVector2f){map->scaling_factor, map->scaling_factor});
    sfSprite_setPosition(map->doors[i]->sprite, (sfVector2f)
    {pos.x * map->block_size, pos.y * map->block_size});
    map->doors[i]->name = str_alloc(doors_name[i > 1 ? 2 : i]);
    if (i > 1) {
        tmp = my_itoa(i - 1);
        map->doors[i]->name = str_replace(map->doors[i]->name, "$", tmp);
        free(tmp);
    }
    map->doors[i]->is_active = 1;
}

void create_button(map_t *map, int i, sfVector2i pos)
{
    map->buttons[i] = malloc(sizeof(struct setting_button));
    map->buttons[i]->texture =
    sfTexture_createFromFile("ressources/sbtn.png", NULL);
    map->buttons[i]->sprite = sfSprite_create();
    sfSprite_setTexture(map->buttons[i]->sprite, map->buttons[i]->texture, 1);
    sfSprite_scale(map->buttons[i]->sprite,
        (sfVector2f){map->scaling_factor, map->scaling_factor});
    sfSprite_setPosition(map->buttons[i]->sprite, (sfVector2f)
    {pos.x * map->block_size, pos.y * map->block_size});
    sfSprite_setTextureRect(map->buttons[i]->sprite, (sfIntRect)
    {0, 0, B_SIZE, B_SIZE});
    map->buttons[i]->font = sfFont_createFromFile("ressources/font.ttf");
    map->buttons[i]->text =
    create_text(map->buttons[i]->font, button_name[i], (sfVector2f){pos.x *
    map->block_size + map->block_size / 2, pos.y * map->block_size}, 20);
    map->buttons[i]->dvalue =
    create_text(map->buttons[i]->font, dval[i], (sfVector2f){pos.x *
    map->block_size + map->block_size / 2, pos.y * map->block_size}, 15);
    map->buttons[i]->is_active = 1;
    map->buttons[i]->value = 1;
}
