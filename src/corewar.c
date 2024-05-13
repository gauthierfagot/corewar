/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** fightiiiiiing
*/

#include <stdbool.h>
#include <stdlib.h>
#include "macros.h"
#include "parameters.h"
#include "functions.h"
#include "arena.h"
#include "op.h"
#include "instructions.h"
#include "mini_printf.h"


static int count_alive_champs(parameters_t *parameters)
{
    int count = 0;

    for (int i = 0; parameters->champions[i] != NULL; ++i) {
        if (parameters->champions[i]->alive)
            ++count;
    }
    return count;
}

static bool launch_arena(parameters_t *parameters)
{
    arena_t *arena = init_arena(parameters);

    if (arena == NULL)
        return false;
    for (int i = 0; count_alive_champs(parameters) > 1; i++) {
        start_fight(parameters, arena->arena, arena->heads);
    }
    if (*arena->heads != NULL)
        mini_printf("The player %d (%s) has won.\n",
            (*arena->heads)->number, (*arena->heads)->name);
    free_arena(arena);
    free_parameters(parameters);
    return true;
}

int corewar(char **argv)
{
    parameters_t *parameters = get_parameters(argv);

    if (parameters == NULL)
        return ERROR;
    init_champion_address(parameters);
    if (!launch_arena(parameters))
        return ERROR;
    return SUCCESS;
}
