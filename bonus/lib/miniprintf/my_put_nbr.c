/*
** EPITECH PROJECT, 2023
** my put nbr
** File description:
** display a int
*/

#include "header.h"

void display_numbers(int nb, long long a, long long i, char x)
{
    x = '0' + ((nb / i) % 10);
    if (a == 1 && i == 1) {
            x = x + 1;
    }
    my_putchar(x);
}

long long i_value(int nb, long long i)
{
    i = 1;
    while ((nb % (i * 10)) < nb) {
        i = i * 10;
    }
    return (i);
}

int my_put_nbr(int nb)
{
    long long i;
    long long a;
    char x;

    a = 0;
    if (nb < 0) {
        my_putchar('-');
        if (nb == -2147483648) {
            nb = (nb + 1) * (-1);
            a = 1;
        } else {
        nb = nb * (-1);
        }
    }
    i = i_value(nb, i);
    while (i >= 1) {
        display_numbers(nb, a, i, x);
        i = i / 10;
    }
}
