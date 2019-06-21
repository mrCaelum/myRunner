/*
** EPITECH PROJECT, 2019
** lib_str
** File description:
** Basical functions
*/

#include "str.h"

int str_length(char const *str)
{
    int count = 0;

    if (!str)
        return (0);
    while (str[count])
        count++;
    return (count);
}

char *str_alloc(char const *str)
{
    char *new = !str ? NULL : malloc((str_length(str) + 1) * sizeof(char));
    int i = 0;

    if (!new)
        return (NULL);
    for (i = 0; str[i]; i++)
        new[i] = str[i];
    new[i] = 0;
    return (new);
}

void str_copy(char *dest, char const *str)
{
    if (!dest || !str)
        return;
    for (int i = 0; str[i]; i++)
        dest[i] = str[i];
}

char *str_concat(char const *str1, char const *str2)
{
    char *str = malloc(str_length(str1) + str_length(str2) + 1);
    int i = 0;

    if (str1)
        for (; (*str1); str1++, i++)
            str[i] = (char)(*str1);
    if (str2)
        for (; (*str2); str2++, i++)
            str[i] = (char)(*str2);
    str[i] = 0;
    return (str);
}

char *str_reverse(char *str)
{
    char tmp;

    if (!str)
        return (NULL);
    for (int i = 0, j = str_length(str) - 1; i <= j; i++, j--) {
        tmp = str[j];
        str[j] = str[i];
        str[i] = tmp;
    }
    return (str);
}
