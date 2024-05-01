/*
** EPITECH PROJECT, 2023
** print arg
** File description:
** fonctions that print specific flag arg for mini_printf.c
*/

#include <stdarg.h>
#include <unistd.h>
#include "header.h"

int print_str(va_list ap, int *f, char c)
{
    char *str;

    str = va_arg(ap, char *);
    my_putstr(str);
    *f = *f + my_strlen(str) - 1;
}

int print_int(va_list ap, int *f, char c)
{
    int nb;

    nb = va_arg(ap, int);
    my_put_nbr(nb);
    *f = *f + count_char(nb);
}

int print_char(va_list ap, int *f, char c)
{
    char ch;

    ch = (char) va_arg(ap, int);
    my_putchar(ch);
}

int print_pourcentage(va_list ap, int *f, char c)
{
    my_putchar('%');
}

int print_other(va_list ap, int *f, char c)
{
    my_putchar('%');
    my_putchar(c);
    *f = *f + 1;
}
