/*
** EPITECH PROJECT, 2019
** lib-str
** File description:
** Tab strings functions
*/

#include "str.h"

static int get_len(char *str, char separator)
{
    int len = 1;
    int i = 0;

    for (; str[i]; i++) {
        len += str[i] == separator;
        for (; str[i] == separator; ++i);
    }
    if (str[i - 2] == separator)
        len--;
    return (len);
}

char **str_to_tab(char *str, char separator)
{
    char **tab = NULL;
    int len = 0;

    if (!str)
        return (NULL);
    for (; (*str) == separator; ++str);
    len = get_len(str, separator);
    tab = malloc((len + 1) * sizeof(char *));
    if (!tab)
        return (NULL);
    for (int i = 0, j = 0; str[i]; i++) {
        if (i == 0)
            tab[j++] = &str[0];
        else if (!str[i - 1] && str[i] != separator)
            tab[j++] = &str[i];
        if (str[i] == separator)
            str[i] = 0;
    }
    tab[len] = NULL;
    return (tab);
}

char *tab_to_str(char **tab, char separator)
{
    char *str;
    int len = 0;
    int size = 0;

    for (; tab[len]; len++);
    for (int i = 0; tab[i]; size += str_length(tab[i]), i++);
    size += (separator ? len - 1 : 0) + 1;
    str = malloc(size * sizeof(char));
    for (int i = 0, y = 0; tab[y]; y++) {
        for (int x = 0; tab[y][x]; x++, i++)
            str[i] = tab[y][x];
        if (separator)
            str[i++] = separator;
    }
    str[size - 1] = 0;
    free(tab);
    return (str);
}
