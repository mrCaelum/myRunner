/*
** EPITECH PROJECT, 2019
** lib_str
** File description:
** str_nbr functions
*/

#include "str.h"

char *int_to_str(int nb)
{
    char *str;
    int size = 1;

    for (int i = nb; i > 9; i /= 10, size++);
    str = malloc((size + 1) * sizeof(char));
    str[size--] = 0;
    for (int i = size; i >= 0; i--) {
        str[i] = nb % 10 + '0';
        nb /= 10;
    }
    return (str);
}

char *my_itoa(int nb)
{
    char *str;
    int size = 1;
    _Bool neg = nb < 0;

    if (neg) {
        nb = -nb;
        size++;
    }
    for (int i = nb; i > 9; i /= 10, size++);
    str = malloc((size + 1) * sizeof(char));
    if (!str)
        return (NULL);
    str[size--] = 0;
    for (; size >= 0; size--) {
        str[size] = nb % 10 + '0';
        nb /= 10;
    }
    if (neg)
        str[0] = '-';
    return (str);
}