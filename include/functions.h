/*
** EPITECH PROJECT, 2024
** functions
** File description:
** functions prototypes for corewar
*/

#ifndef FUNCTIONS_H
    #define FUNCTIONS_H

    #include <stdbool.h>
    #include "parameters.h"

int corewar(char **);

void print_help(void);

//parameters
parameters_t *get_parameters(char **argv);
void free_parameters(parameters_t *params);
bool set_champions_numbers(champion_t **champions);

#endif
