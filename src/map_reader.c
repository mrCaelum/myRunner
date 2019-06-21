/*
** EPITECH PROJECT, 2018
** MUL_my_runner_2018
** File description:
** Level reader
*/

#include "game.h"

static struct tab_map_entity_id tab_enty[] = {
    {'.', NULL, &create_coin},
    {'~', NULL, &create_spike},
    {'o', NULL, &create_eye},
    {'D', NULL, &create_door},
    {'B', NULL, &create_button},
    {0, NULL}
};

static map_t *open_failed(char const *file, int md)
{
    int size = 0;

    while (file[size])
        size++;
    if (md)
        write(2, "\e[31m[ERROR]\e[37m Invalid map : '", 34);
    else
        write(2, "\e[31m[ERROR]\e[37m Unable to open : '", 37);
    write(2, file, size);
    write(2, "'\n", 2);
    return (NULL);
}

static void setup_map_settings(map_t *map, options_t opt)
{
    map->running = 1;
    map->opt = opt;
    map->init_pos = (sfVector2f){0, 0};
    map->scaling_factor = (float)opt.height / (float)(map->height * B_SIZE);
    map->block_size = map->scaling_factor * B_SIZE;
    map->m_preview = create_money_preview(opt.money);
}

static int check_map(char *buffer, int map_size, map_t *map, options_t opt)
{
    int i = 0;

    for (int i = 0; tab_enty[i].id; i++) {
        map->nb[i] = 0;
        tab_enty[i].ptr = &map->nb[i];
    }
    for (i = 0; i < map_size; i++) {
        if (!check_map_char(buffer[i]))
            return (1);
        for (int j = 0; tab_enty[j].id; j++)
            (*tab_enty[j].ptr) += buffer[i] == tab_enty[j].id;
        if (!map->width && buffer[i] == '\n')
            map->width = i;
        else if (buffer[i] == '\n' && (i - map->height) % map->width)
            return (1);
        map->height += buffer[i] == '\n';
    }
    setup_map_settings(map, opt);
    return (0);
}

static char *get_buffer(char const *tmp_buffer, int map_size)
{
    char *buffer = malloc(sizeof(char) * (map_size + 1));
    if (!buffer)
        return (NULL);
    for (int i = 0; i < map_size + 1; i++)
        buffer[i] = tmp_buffer[i];
    return (buffer);
}

map_t *map_reader(char const *file, options_t opt)
{
    map_t *map = malloc(sizeof(map_t));
    char tmp_buffer[MAX_MAP_SIZE];
    char *buffer = NULL;
    int map_size;
    int fd = open(file, O_RDONLY);
    char tmp;

    if (!map || fd < 0)
        return (open_failed(file, 0));
    *map = (map_t){};
    map_size = read(fd, tmp_buffer, MAX_MAP_SIZE);
    if (read(fd, &tmp, 1) || tmp_buffer[0] == '\n')
        return (open_failed(file, 1));
    close(fd);
    buffer = get_buffer(tmp_buffer, map_size);
    if (check_map(buffer, map_size, map, opt) || fill_map(map, buffer))
        return (open_failed(file, 1));
    free(buffer);
    return (map);
}
