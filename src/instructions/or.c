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
    int index)
{
    unsigned char reg = 0;

    extract_data_arena(arena, index, REG_SIZE_FILE, (char *)&reg);
    if (reg == 0 || reg > REG_NUMBER) {
        head->carry = false;
        return;
    }
    head->registers[reg - 1] = result[0] | result[1];
    head->carry = true;
}

static int get_value_arena(head_t *head, char *arena, int byte_size,
    int index)
{
    int value = 0;

    extract_data_arena(arena, index, byte_size, (char *)&value);
    if (byte_size == REG_SIZE_FILE) {
        if (value <= 0 || value > REG_NUMBER)
            return 0;
        return head->registers[value - 1];
    }
    if (byte_size == IND_SIZE_FILE) {
        extract_data_arena(arena, (head->index + value % IDX_MOD) % MEM_SIZE,
            DIR_SIZE_FILE, (char *)&value);
        return value;
    }
    return value;
}

void instruction_or(head_t *head, char *arena, parameters_t *)
{
    char *coding_byte = NULL;
    int tmp = 0;
    int byte_size = 0;
    int index = 0;
    int value[2] = {0};

    index = (head->index + 2) % MEM_SIZE;
    coding_byte = dec_to_bin((unsigned char)arena[index - 1]);
    if (coding_byte == NULL) {
        head->carry = false;
        return;
    }
    for (int i = 0; i < 2; ++i) {
        byte_size = search_byte_size(coding_byte, &tmp);
        value[i] = get_value_arena(head, arena, byte_size, index);
        index += byte_size;
    }
    add_result_in_arena(head, arena, value, index);
    head->index = (index + 1) % MEM_SIZE;
    free(coding_byte);
}
