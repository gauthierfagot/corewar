/*
** EPITECH PROJECT, 2023
** header
** File description:
** header for mini_prinf
*/

#ifndef MINI_H
    #define MINI_H

    #include <stdarg.h>
    #include <unistd.h>
    #include <stdlib.h>

int count_char(int nb);
int print_string(va_list ap, const char *format, int *i, int *nb);
int mini_printf(const char *format, ...);
int print_str(va_list ap, int *f, char c);
int print_int(va_list ap, int *f, char c);
int print_char(va_list ap, int *f, char c);
int print_pourcentage(va_list ap, int *f, char c);
int print_other(va_list ap, int *f, char c);
void my_putchar(char c);
int my_putstr(char const *str);
void display_numbers(int nb, long long a, long long i, char x);
long long i_value(int nb, long long i);
int my_put_nbr(int nb);
int my_strlen(char const *str);

#endif
