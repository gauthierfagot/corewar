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

static void remove_head(head_t **heads)
{
    head_t *tmp = *heads;

    *heads = (*heads)->next;
    free(tmp);
}

static bool is_head_alive(parameters_t *parameters, head_t *head)
{
    for (int i = 0; parameters->champions[i] != NULL; ++i) {
        if (parameters->champions[i]->number == head->number &&
            parameters->champions[i]->last_alive < CYCLE_TO_DIE) {
            parameters->champions[i]->alive = false;
            return true;
        }
    }
    return false;
}

static bool handle_wait(parameters_t *parameters, char *arena, head_t **heads)
{
    if ((*heads)->wait_cycle > 0) {
        (*heads)->wait_cycle -= 1;
        start_fight(parameters, arena, &(*heads)->next);
        return true;
    } else if ((*heads)->wait_cycle == 0) {
        (*heads)->instruction(*heads, arena, parameters);
        (*heads)->wait_cycle -= 1;
        start_fight(parameters, arena, &(*heads)->next);
        return true;
    }
    return false;
}

static void start_fight(parameters_t *parameters, char *arena, head_t **heads)
{
    if (*heads == NULL)
        return;
    if (!is_head_alive(parameters, *heads)) {
        remove_head(heads);
        start_fight(parameters, arena, heads);
        return;
    }
    if (handle_wait(parameters, arena, heads))
        return;
    for (int i = 1; i <= NB_OF_INSTRUCTIONS + 1; i++) {
        if (arena[(*heads)->index] == i) {
            (*heads)->wait_cycle = op_tab[i - 1].nbr_cycles;
            (*heads)->instruction = INSTRUCTIONS[i];
            start_fight(parameters, arena, &(*heads)->next);
            return;
        }
    }
    remove_head(heads);
    start_fight(parameters, arena, heads);
}

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
    print_arena(arena);
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
