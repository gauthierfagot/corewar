/*
** EPITECH PROJECT, 2023
** my put char
** File description:
** display a character
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
