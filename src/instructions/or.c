/*
** EPITECH PROJECT, 2024
** or
** File description:
** or
*/

#include <stdint.h>
#include "arena.h"
#include "parameters.h"
#include "mini_printf.h"
#include "instructions.h"
#include "functions.h"

static void add_result_in_arena(head_t *head, char *arena, int *result,
    int *size_value)
{
    unsigned char reg = 0;

    extract_data_arena(arena, (head->index + 2 + size_value[0] +
        size_value[1]) % MEM_SIZE, REG_SIZE_FILE, (char *)&reg);
    if (reg == 0 || reg > REG_NUMBER) {
        head->carry = false;
        return;
    }
    head->registers[reg - 1] = result[0] | result[1];
    head->carry = true;
}

static int get_first_value(head_t *head, char *arena, int *size_value,
    bool *error)
{
    int value = 0;

    extract_data_arena(arena, (head->index + 2)
        % MEM_SIZE, size_value[0], (char *)&value);
    if (size_value[0] == REG_SIZE_FILE) {
        if (value <= 0 || value > REG_NUMBER) {
            *error = true;
            return 0;
        }
        return head->registers[value - 1];
    }
    if (size_value[0] == IND_SIZE_FILE) {
        extract_data_arena(arena, (head->index + value % IDX_MOD) % MEM_SIZE,
            DIR_SIZE_FILE, (char *)&value);
        return value;
    }
    return value;
}

static int get_second_value(head_t *head, char *arena, int *size_value,
    bool *error)
{
    int value = 0;

    extract_data_arena(arena, (head->index + 2 + size_value[0])
        % MEM_SIZE, size_value[1], (char *)&value);
    if (size_value[1] == REG_SIZE_FILE) {
        if (value <= 0 || value > REG_NUMBER) {
            *error = true;
            return 0;
        }
        return head->registers[value - 1];
    }
    if (size_value[1] == IND_SIZE_FILE) {
        extract_data_arena(arena, (head->index + value % IDX_MOD) % MEM_SIZE,
            DIR_SIZE_FILE, (char *)&value);
        return value;
    }
    return value;
}

static bool get_value_arena(head_t *head, char *arena, int *size_value,
    int value[2])
{
    bool error = false;

    value[0] = get_first_value(head, arena, size_value, &error);
    if (error)
        return false;
    value[1] = get_second_value(head, arena, size_value, &error);
    if (error)
        return false;
    return true;
}

void instruction_or(head_t *head, char *arena, parameters_t *)
{
    int value[2] = {0};
    int size_value[2] = {0};

    extract_arguments_size(2, arena, head, size_value);
    if (!get_value_arena(head, arena, size_value, value)) {
        head->carry = false;
        head->index = (head->index + 3 + size_value[0] + size_value[1])
        % MEM_SIZE;
        return;
    }
    add_result_in_arena(head, arena, value, size_value);
    head->index = (head->index + 3 + size_value[0] + size_value[1]) % MEM_SIZE;
}
