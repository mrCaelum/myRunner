/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Opt functions
*/

#include "game.h"
#define READ_SIZE 64

static void fill(options_t *opt, char c, int j)
{
    if (!j)
        opt->width = opt->width * 10 + c - 48;
    else if (j == 1)
        opt->height = opt->height * 10 + c - 48;
    else if (j == 2)
        opt->fullscreen = (c - 48) ? sfFullscreen : sfNone;
    else if (j == 3)
        opt->framerate = opt->framerate * 10 + c - 48;
    else
        opt->v_sync = (c - 48) ? sfTrue : sfFalse;
}

static void write_int(int fd, int nb)
{
    char c;

    if (nb < 0) {
        nb *= -1;
        write(fd, "-", 1);
    }
    if (nb < 10) {
        c = nb + '0';
        write(fd, &c, 1);
    } else {
        write_int(fd, nb / 10);
        c = nb % 10 + '0';
        write(fd, &c, 1);
    }
}

options_t get_options(unsigned int *money)
{
    options_t opt = (options_t){0, 0, sfNone, 0, sfFalse, money};
    int fd = 0;
    int readed = 0;
    char buffer[READ_SIZE];

    if ((fd = open("opt.save", O_RDONLY)) < 0)
        return ((options_t){1920, 1080, sfFullscreen, 60, sfTrue, money});
    readed = read(fd, buffer, READ_SIZE);
    for (int i = 0, j = 0; i < readed && j < 5 && buffer[i] != ';'; i++) {
        if (buffer[i] == ',' || buffer[i] == ';')
            j++;
        else if (buffer[i] < '0' || buffer[i] > '9')
            return ((options_t){1920, 1080, sfFullscreen, 60, sfTrue, money});
        else
            fill(&opt, buffer[i], j);
    }
    close(fd);
    return (opt);
}

static char *get_opt_element(struct setting_button **button, int nb)
{
    char *screen_r = str_alloc(sfText_getString(button[0]->dvalue));
    char **tab_r = str_to_tab(screen_r, 'x');
    char *str = str_concat(tab_r[0], ",");
    char *tmp = str_concat(str, tab_r[1]);

    free(str);
    str = str_concat(tmp, button[1]->value ? ",1," : ",0,");
    free(tmp);
    tmp = str_concat(str, sfText_getString(button[2]->dvalue));
    free(str);
    str = str_concat(tmp, button[3]->value ? ",1;" : ",0;");
    free(tmp);
    free(tab_r);
    free(screen_r);
    return (str);
}

void set_options(struct setting_button **button, int nb)
{
    char *str = get_opt_element(button, nb);
    int fd = 0;

    if ((fd = open("opt.save", O_WRONLY)) < 0)
        return;
    write(fd, str, str_length(str));
    free(str);
    close(fd);
}
