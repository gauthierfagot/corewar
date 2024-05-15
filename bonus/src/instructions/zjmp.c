/*
** EPITECH PROJECT, 2024
** zjmp
** File description:
** zjmp
*/

#include "arena.h"
#include "parameters.h"
#include "mini_printf.h"
#include "functions.h"

void instruction_zjmp(head_t *head, byte_t *arena, parameters_t *)
{
    __int16_t direct = 0;

    extract_data_arena(arena,
        (head->index + 1) % MEM_SIZE, 2, (char *)&direct);
    if (head->carry == true)
        head->index = head->index + direct % IDX_MOD;
    else
        head->index = ((head->index + 1) % MEM_SIZE) % MEM_SIZE;
}
