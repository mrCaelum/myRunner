/*
** EPITECH PROJECT, 2019
** lib_str
** File description:
** String library
*/

#ifndef STR_H_
#define STR_H_

#include <unistd.h>
#include <stdlib.h>

int str_length(const char const *str);
char *str_alloc(const char const *str);
void str_copy(char *dest, char const *str);
char *str_concat(char const *str1, char const *str2);
char *str_reverse(char *str);
void str_replace_char(char *str, char c1, char c2);
char *str_replace(char *str, char const *str1, char const *str2);
char *str_remove_char(char *str, char c);
char *sub_str(char const *str, char separator);
char *str_upcase(char *str);
char **str_to_tab(char *str, char separator);
char *tab_to_str(char **tab, char separator);
int str_contains(char const *str, char c);
int str_is_equal(char const *str, char const *comp);
int str_compare(char const *str, char const *comp, int n);
int str_startwith(char const *str, char const *comp);
int str_endwith(char const *str, char const *comp);
char *int_to_str(int nb);
char *my_itoa(int nb);

#endif
