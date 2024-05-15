/*
** EPITECH PROJECT, 2023
** lib
** File description:
** lib
*/

#pragma once

    #include <stdbool.h>

int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
void my_puterr(const char *);
int my_strcmp(char const *s1, char const *s2);
char *read_buffer(const char *filepath);
char *my_strdup(const char *str);
int my_compute_power_rec(int nb, int p);
int my_arraylen(char **);
void free_array(char **);
char **format_line(char *line, const char *separators, const char *ignorers);
bool is_number(char *);
bool is_alpha(char *);
int str_to_int(char *);
char *get_buffer(char const *const path);
