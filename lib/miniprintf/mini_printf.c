/*
** EPITECH PROJECT, 2023
** upgrade of miniprintf
** File description:
** trying to write mini printf better
*/

#include <stdarg.h>
#include "header.h"
#include "struct.h"

int count_char(int nb)
{
    int count = 0;

    if (nb < 0) {
        while (nb < -9) {
            count = count + 1;
            nb = nb / 10;
        }
        count = count + 1;
        return (count);
    }
    while (nb > 9) {
        count = count + 1;
        nb = nb / 10;
    }
    return (count);
}

int print_string(va_list ap, const char *format, int *i, int *nb)
{
    if (format[*i] != '%') {
        my_putchar(format[*i]);
        return (0);
    }
    if (format[*i + 1] == ' ') {
        my_putchar(' ');
        *nb = *nb + 1;
    }
    while (format[*i + 1] == ' ')
        *i = *i + 1;
    for (int a = 0; tableau[a].fonction != 0; a++) {
        if (tableau[a].flag == format[*i + 1] || tableau[a].flag == '\0') {
            tableau[a].fonction(ap, nb, format[*i + 1]);
            break;
        }
    }
    *i = *i + 1;
    return (-1);
}

int mini_printf(const char *format, ...)
{
    va_list ap;
    int i = 0;
    int *place;
    int compteur = 0;
    int *nb;

    for (int f = 0; format[f] != '\0'; f++) {
        if (f != 0 && format[f - 1] == '%' && format[f] == '%')
            continue;
        if (format[f] == '%' && format[f + 1] == '\0')
            return (-1);
    }
    nb = &compteur;
    place = &i;
    va_start(ap, format);
    for (i; format[i] != '\0'; i++) {
        print_string(ap, format, place, nb);
        compteur = compteur + 1;
    }
    return (compteur);
}
