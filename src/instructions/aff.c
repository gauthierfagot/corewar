/*
** EPITECH PROJECT, 2024
** aff
** File description:
** aff
*/

#include "arena.h"
#include "parameters.h"
#include "mini_printf.h"
#include "instructions.h"

void extract_data_arena(char *arena, int index, int byte_size, char *result)
{
    int tmp_size = byte_size - 1;

    if (byte_size > 4 || index + byte_size >= MEM_SIZE)
        return;
    for (int i = 0; i < byte_size; ++i) {
        result[tmp_size] = arena[index];
        ++index;
        --tmp_size;
    }
}

void instruction_aff(head_t *head, char *arena, parameters_t *parameters)
{
    int *reg = 0;

    ++head->index;
    extract_data_arena(arena, head->index, 1, (char *)&reg);
    if (reg <= 0 || reg > 16)
        return;
    mini_printf("%d\n", head->registers[reg]);
    head->index = (head->index + REG_SIZE + 1) % MEM_SIZE;
    free(reg);
}
