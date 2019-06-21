/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** Text function
*/

#include "game.h"

sfText *create_text(sfFont *font, char const *str, sfVector2f pos, int size)
{
    sfText *text = sfText_create();

    pos.y -= size == 20 ? 300 : -30;
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, 0.7);
    sfText_setCharacterSize(text, size);
    pos.x -= sfText_getGlobalBounds(text).width / 2;
    sfText_setPosition(text, pos);
    return (text);
}
