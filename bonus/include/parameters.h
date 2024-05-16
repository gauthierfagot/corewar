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
    char name[PROG_NAME_LENGTH + 1];
    int load_address;
    char *path;
    int last_alive;
    bool alive;
    int color;
}champion_t;

typedef struct parameters_s {
    int dump;
    int cycles;
    int live_counter;
    champion_t **champions;
}parameters_t;
