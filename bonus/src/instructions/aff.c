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

void instruction_aff(head_t *head, byte_t *arena, parameters_t *)
{
    unsigned char reg = 0;

    extract_data_arena(arena, head->index + 2, REG_SIZE_FILE, (char *)&reg);
    if (reg == 0 || reg > REG_NUMBER)
        return;
    mini_printf("%c\n", (head->registers[reg - 1] % ASCII_SIZE));
    head->index = (head->index + REG_SIZE_FILE + 2) % MEM_SIZE;
}
