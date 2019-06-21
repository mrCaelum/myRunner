/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Settings buttons functions
*/

#include "game.h"

static const char const *resolutions[] = {
    "1280x720",
    "1920x1080",
    "2048x1080",
    "3840x2160",
    "7680x4320",
    "800x600",
    NULL
};

static const char const *fps[] = {
    "30",
    "60",
    "120",
    "150",
    "300",
    "600",
    NULL
};

static const char const *active[] = {
    "OFF",
    "ON",
    NULL
};

static void edit_button(struct setting_button *button, map_t *map, int i)
{
    if (map->buttons[i]->is_active) {
        map->buttons[i]->is_active = 0;
        sfSprite_setTextureRect(button->sprite, (sfIntRect)
        {B_SIZE, 0, B_SIZE, B_SIZE});
        button->value = !i ?
        resolutions[button->value + 1] ? button->value + 1 : 0
        : i == 2 ? fps[button->value + 1] ? button->value + 1 : 0
        : active[button->value + 1] ? button->value + 1 : 0;
        sfText_setString(button->dvalue, !i ? resolutions[button->value]
        : i == 2 ? fps[button->value] : active[button->value]);
    }
}

void update_buttons(map_t *map, player_t *player)
{
    sfFloatRect p_bounds = sfSprite_getGlobalBounds(player->sprite);

    for (int i = 0; i < map->nb[SBTN]; i++) {
        if (is_point_in((sfVector2f){p_bounds.left,
            p_bounds.top + p_bounds.height}, map->buttons[i]->sprite)
        && is_point_in((sfVector2f){p_bounds.left + p_bounds.width,
            p_bounds.top + p_bounds.height}, map->buttons[i]->sprite))
            edit_button(map->buttons[i], map, i);
        else {
            sfSprite_setTextureRect(map->buttons[i]->sprite, (sfIntRect)
            {0, 0, B_SIZE, B_SIZE});
            map->buttons[i]->is_active = 1;
        }
    }
}
