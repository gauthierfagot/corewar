/*
** EPITECH PROJECT, 2024
** fight
** File description:
** one cycle
*/

#include <stdbool.h>
#include <stdlib.h>
#include "arena.h"
#include "parameters.h"
#include "instructions.h"
#include "functions.h"

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
            parameters->champions[i]->last_alive > parameters->cycles) {
            parameters->champions[i]->alive = false;
            return false;
        }
    }
    return true;
}

void start_fight(parameters_t *parameters, char *arena, head_t **heads)
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
    for (unsigned char i = 1; i <= NB_OF_INSTRUCTIONS + 1; i++) {
        if (arena[(*heads)->index] == i) {
            (*heads)->wait_cycle = op_tab[i - 1].nbr_cycles;
            (*heads)->instruction = INSTRUCTIONS[i];
            start_fight(parameters, arena, &(*heads)->next);
            return;
        }
    }
    (*heads)->index = ((*heads)->index + 1) % MEM_SIZE;
    start_fight(parameters, arena, &(*heads)->next);
}
