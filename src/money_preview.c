/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2018
** File description:
** money_preview
*/

#include "game.h"

struct money_preview create_money_preview(unsigned int const *money)
{
    struct money_preview pw = (struct money_preview){
        sfTexture_createFromFile("ressources/coin.png", NULL),
        sfSprite_create(),
        sfFont_createFromFile("ressources/font.ttf"),
        sfText_create(), money
    };

    if (!pw.texture || !pw.sprite || !pw.font || !pw.text)
        return ((struct money_preview){});
    sfSprite_setTexture(pw.sprite, pw.texture, sfTrue);
    sfSprite_setPosition(pw.sprite, (sfVector2f){10, 10});
    sfSprite_setScale(pw.sprite, (sfVector2f){0.6, 0.6});
    sfSprite_setTextureRect(pw.sprite, (sfIntRect){0, 0, 64, 64});
    sfText_setString(pw.text, "0");
    sfText_setFont(pw.text, pw.font);
    sfText_setOutlineColor(pw.text, sfBlack);
    sfText_setOutlineThickness(pw.text, 0.7);
    sfText_setPosition(pw.text, (sfVector2f){62, 10});
    sfText_setCharacterSize(pw.text, 34);
    return (pw);
}

void update_money_preview(struct money_preview *m_preview)
{
    sfIntRect rect = sfSprite_getTextureRect(m_preview->sprite);
    char *str = int_to_str(*m_preview->money);

    rect.left = rect.left >= 15 * 64 ? 0 : rect.left + 64;
    sfSprite_setTextureRect(m_preview->sprite, rect);
    sfText_setString(m_preview->text, str);
    free(str);
}

void destroy_money_preview(struct money_preview *m_preview)
{
    sfSprite_destroy(m_preview->sprite);
    sfTexture_destroy(m_preview->texture);
    sfText_destroy(m_preview->text);
}
