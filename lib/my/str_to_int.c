/*
** EPITECH PROJECT, 2024
** str to int
** File description:
** str to int
*/

#include "lib.h"

int str_to_int(char *str)
{
    int nb = 0;

    for (int i = 0; str[i] != '\0' && str[i] != '#'; i++) {
        nb *= 10;
        nb += str[i] - '0';
    }
    return nb;
}
