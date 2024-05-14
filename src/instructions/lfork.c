/*
** EPITECH PROJECT, 2024
** lfork
** File description:
** lfork
*/

#include "arena.h"
#include "parameters.h"
#include "mini_printf.h"
#include "functions.h"

static head_t *duplicate_head(head_t *head)
{
    head_t *new = malloc(sizeof(head_t));

    new->carry = head->carry;
    new->index = head->index;
    new->instruction = NULL;
    new->next = NULL;
    new->number = head->number;
    for (int i = 0; i < REG_NUMBER; ++i)
        new->registers[i] = head->registers[i];
    new->wait_cycle = -1;
    return new;
}

void instruction_lfork(head_t *head, char *arena, parameters_t *)
{
    __int16_t direct = 0;
    head_t *duplicate = duplicate_head(head);

    if (duplicate == NULL)
        return;
    extract_data_arena(arena, head->index + 1, 2, (char *)&direct);
    duplicate->index = (duplicate->index + direct) % MEM_SIZE;
    push_index_head(head, duplicate);
    head->index = (head->index + 3) % MEM_SIZE;
}
