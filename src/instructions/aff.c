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
#include "functions.h"

void instruction_aff(head_t *head, char *arena, parameters_t *parameters)
{
    unsigned char reg = 0;

    head->index = (head->index + 2) % MEM_SIZE;
    extract_data_arena(arena, head->index, REG_SIZE_FILE, (char *)&reg);
    if (reg == 0 || reg > REG_NUMBER)
        return;
    mini_printf("%d\n", head->registers[reg - 1] % ASCII_SIZE);
    head->index = (head->index + REG_SIZE_FILE) % MEM_SIZE;
}
