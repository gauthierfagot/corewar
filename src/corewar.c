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
#include <stdint.h>

static int count_alive_champs(parameters_t *parameters)
{
    int count = 0;

    for (int i = 0; parameters->champions[i] != NULL; ++i) {
        if (parameters->champions[i]->alive)
            ++count;
    }
    return count;
}

static void update_lives(parameters_t *parameters)
{
    for (int i = 0; parameters->champions[i] != NULL; ++i) {
        parameters->champions[i]->last_alive += 1;
    }
    if (parameters->live_counter > NBR_LIVE) {
        parameters->cycles -= CYCLE_DELTA;
        parameters->live_counter -= NBR_LIVE;
    }
}

static void print_won(head_t *winner, parameters_t *parameters)
{
    for (int i = 0; parameters->champions[i] != NULL; ++i) {
        if (parameters->champions[i]->number == winner->number) {
            mini_printf("The player %d (%s) has won.\n",
                parameters->champions[i]->number,
                parameters->champions[i]->name);
        }
    }
}

static bool launch_arena(parameters_t *parameters)
{
    arena_t *arena = init_arena(parameters);

    if (arena == NULL)
        return false;
    for (int i = 0; count_alive_champs(parameters) > 1; i++) {
        if (parameters->dump == i) {
            print_arena(arena);
        }
        start_fight(parameters, arena->arena, arena->heads);
        update_lives(parameters);
    }
    if (*arena->heads != NULL)
        print_won(*arena->heads, parameters);
    else
        mini_printf("Everybody is dead... :(\n");
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
