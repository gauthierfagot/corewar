/*
** EPITECH PROJECT, 2024
** my_puterr
** File description:
** my_puterr
*/
#include <unistd.h>
#include "lib.h"

void my_puterr(const char *str)
{
    write(2, str, my_strlen(str));
}
