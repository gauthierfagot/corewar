/*
** EPITECH PROJECT, 2024
** parameters
** File description:
** struct
*/

#ifndef PARAMETERS_STRUCT_H
    #define PARAMETERS_STRUCT_H

    #include <stddef.h>

typedef struct champion_s {
    int number;
    int load_adress;
    char *path;
}champion_t;

typedef struct parameters_s {
    int dump;
    char *arena;
    champion_t **champions;
}parameters_t;

#endif
