/*
** EPITECH PROJECT, 2023
** my_strdup
** File description:
** my_strdup
*/
#include <stdlib.h>
#include "lib.h"

char *my_strdup(char const *src)
{
    int n = my_strlen(src);
    char *dest = malloc(sizeof(char) * (n + 1));

    dest = my_strcpy(dest, src);
    return dest;
}
