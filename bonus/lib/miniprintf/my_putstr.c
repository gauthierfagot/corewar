/*
** EPITECH PROJECT, 2023
** my putstr.c
** File description:
** display a string of characters
*/

#include "header.h"

int my_putstr(char const *str)
{
    int i;

    i = 0;
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i = i + 1;
    }
}
