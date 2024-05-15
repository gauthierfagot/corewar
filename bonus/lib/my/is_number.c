/*
** EPITECH PROJECT, 2024
** is number
** File description:
** is nulber
*/

#include <stdbool.h>

bool is_number(char *str)
{
    for (int i = 0; str[i] != '\0' && str[i] != '#'; i++) {
        if (!('0' <= str[i] && str[i] <= '9'))
            return false;
    }
    return true;
}
