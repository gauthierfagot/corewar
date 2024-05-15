/*
** EPITECH PROJECT, 2023
** header for fontction pointer structs
** File description:
** .
*/

#ifndef HEADER2_H
    #define HEADER2_H

typedef struct check_header {
    char flag;
    int (*fonction)(va_list, int *, char);
} check_header_t;

check_header_t tableau[7] = {
    {'d', print_int},
    {'i', print_int},
    {'s', print_str},
    {'c', print_char},
    {'%', print_pourcentage},
    {'\0', print_other},
    {0, NULL}
};

#endif
