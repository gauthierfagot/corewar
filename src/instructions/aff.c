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
    int reg = 0;

    ++head->index;
<<<<<<< HEAD
    extract_data_arena(arena, head->index, REG_SIZE_FILE, (char *)&reg);
    if (reg <= 0 || reg > REG_NUMBER)
        return;
    mini_printf("%d\n", head->registers[reg] % ASCII_SIZE);
    head->index = (head->index + REG_SIZE + 1) % MEM_SIZE;
=======
    extract_data_arena(arena, head->index, 1, (char *)&reg);
    if (reg <= 0 || reg > REG_NUMBER)
        return;
    mini_printf("%d\n", head->registers[reg]);
    head->index = (head->index + REG_SIZE_FILE + 1) % MEM_SIZE;
>>>>>>> 39ab49ef3ba96691350c6d62b00c3c23f39c622d
}
