/*
** EPITECH PROJECT, 2019
** lib_str
** File description:
** String edit functions
*/

#include "str.h"

void str_replace_char(char *str, char c1, char c2)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == c1)
            str[i] = c2;
}

char *str_replace(char *str, char const *str1, char const *str2)
{
    int size = 0;
    char *new = NULL;

    if (str_is_equal(str, str1)) {
        free(str);
        return (str_alloc(str2));
    }
    for (int i = 0; str[i]; size++, i++)
        if (str_startwith(&str[i], str1)) {
            i += str_length(str1);
            size += str_length(str2);
        }
    new = malloc((size + 1) * sizeof(char));
    for (int i = 0, j = 0; str[j]; i++, j++) {
        if (str_startwith(&str[j], str1)) {
            str_copy(&new[i], str2);
            j += str_length(str1) - 1;
            i += str_length(str2) - 1;
        } else
            new[i] = str[j];
    }
    new[size] = 0;
    free(str);
    return (new);
}

char *str_remove_char(char *str, char c)
{
    int size = 0;
    char *new = NULL;

    for (int i = 0; str[i]; i++, size += str[i] != c);
    new = malloc((size + 1) * sizeof(char));
    for (int i = 0, size = 0; str[i]; i++)
        if (str[i] != c)
            new[size++] = str[i];
    new[size] = 0;
    free(str);
    return (new);
}

char *sub_str(char const *str, char separator)
{
    char *new = NULL;
    int i = 0;

    if (!str)
        return (NULL);
    for (; str[i] && str[i] != separator; i++);
    new = malloc((i + 1) * sizeof(char));
    for (int j = 0; j < i; j++)
        new[j] = str[i];
    new[i] = 0;
    return (new);
}

char *str_upcase(char *str)
{
    char *new = str ? malloc((str_length(str) + 1) * sizeof(char)) : NULL;
    int i = 0;

    if (!new)
        return (NULL);
    for (; str[i]; i++)
        new[i] = str[i] - ((str[i] >= 'a' && str[i] <= 'z') ? 'a' - 'A' : 0);
    new[i] = 0;
    free(str);
    return (new);
}
