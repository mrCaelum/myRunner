/*
** EPITECH PROJECT, 2019
** lib_str
** File description:
** Test functions
*/

#include "str.h"

int str_contains(char const *str, char c)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            return (1);
    return (0);
}

int str_is_equal(char const *str, char const *comp)
{
    int i = 0;

    for (; str[i] || comp[i]; i++)
        if (str[i] != comp[i])
            return (0);
    if (str[i] != comp[i])
        return (0);
    return (1);
}

int str_compare(char const *str, char const *comp, int n)
{
    for (int i = 0; i < n || !str[i] && !comp[i]; i++)
        if (str[i] != comp[i])
            return (0);
    return (1);
}

int str_startwith(char const *str, char const *comp)
{
    for (int i = 0; comp[i]; i++)
        if (str[i] != comp[i])
            return (0);
    return (1);
}

int str_endwith(char const *str, char const *comp)
{
    int i = str_length(str);
    int j = str_length(comp);

    for (; i >= 0 && j >= 0; i--, j--)
        if (str[i] != comp[i])
            return (0);
    return (1);
}
