/*
** EPITECH PROJECT, 2024
** parameters
** File description:
** struct
*/

#pragma once

    #include <stddef.h>
    #include <stdbool.h>
    #include "op.h"

typedef struct champion_s {
    int number;
    int load_address;
    char *path;
    int last_alive;
    bool alive;
}champion_t;

typedef struct parameters_s {
    int dump;
    champion_t **champions;
}parameters_t;
