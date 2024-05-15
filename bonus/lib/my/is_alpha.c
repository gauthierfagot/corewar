/*
** EPITECH PROJECT, 2024
** is_alpha
** File description:
** check if a string is alpha
*/

#include <stdbool.h>

bool is_alpha(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(('0' <= str[i] && str[i] <= '9') ||
            ('a' <= str[i] && str[i] <= 'z') ||
            ('A' <= str[i] && str[i] <= 'Z') ||
            str[i] == '_'))
            return false;
    }
    return true;
}
