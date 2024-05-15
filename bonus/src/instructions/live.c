/*
** EPITECH PROJECT, 2024
** live
** File description:
** instruction live
*/

#include "arena.h"
#include "parameters.h"
#include "functions.h"
#include "mini_printf.h"

void instruction_alive(head_t *head, char *arena, parameters_t *parameters)
{
    int direct = 0;

    extract_data_arena(arena,
        (head->index + 1) % MEM_SIZE, 4, (char *)&direct);
    head->index = (head->index + DIR_SIZE + 1) % MEM_SIZE;
    for (int i = 0; parameters->champions[i] != NULL; ++i) {
        if (parameters->champions[i]->number == direct) {
            // mini_printf("The player %d (%s) is alive.\n",
            //     parameters->champions[i]->number,
            //     parameters->champions[i]->name);
            parameters->champions[i]->last_alive = 0;
        }
    }
    parameters->live_counter += 1;
}
