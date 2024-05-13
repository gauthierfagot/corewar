/*
** EPITECH PROJECT, 2024
** live
** File description:
** instruction live
*/

#include "arena.h"
#include "parameters.h"
#include "mini_printf.h"

void instruction_alive(head_t *head, char *arena, parameters_t *parameters)
{
    mini_printf("The player %d (%s) is alive.\n", head->number, head->name);
    head->index = (head->index + DIR_SIZE + 1) % MEM_SIZE;
}
