/*
** EPITECH PROJECT, 2024
** add
** File description:
** add
*/

#include "arena.h"
#include "parameters.h"
#include "mini_printf.h"

void instruction_add(head_t *head, char *arena, parameters_t *)
{
    unsigned char first = arena[head->index + 2];
    unsigned char second = arena[head->index + 3];
    unsigned char result = arena[head->index + 4];

    if ((first == 0 || second == 0 || result == 0) ||
        first > REG_NUMBER || second > REG_NUMBER || result > REG_NUMBER) {
        head->carry = false;
        head->index = (head->index + 5) % MEM_SIZE;
        return;
    }
    head->carry = true;
    head->registers[result - 1] =
        head->registers[first - 1] + head->registers[second - 1];
    head->index = (head->index + 5) % MEM_SIZE;
}
