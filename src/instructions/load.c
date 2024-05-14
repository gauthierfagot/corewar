/*
** EPITECH PROJECT, 2024
** load
** File description:
** ld
*/

#include "arena.h"
#include "parameters.h"
#include "mini_printf.h"
#include "functions.h"

static void put_dir_in_reg(head_t *head, char *arena)
{
    unsigned char reg = 0;
    int direct = 0;
    int value = 0;

    extract_data_arena(arena, head->index + 2, 1, (char *)&reg);
    if (reg == 0 || reg >= REG_NUMBER) {
        head->carry = false;
        return;
    }
    extract_data_arena(arena,
        (head->index + 3) % MEM_SIZE, 4, (char *)&direct);
    extract_data_arena(arena,
        (head->index + direct) % MEM_SIZE, REG_SIZE, (char *)&value);
    head->registers[reg - 1] = value;
}

static void put_indir_in_reg(head_t *head, char *arena)
{
    unsigned char reg = 0;
    __int16_t indirect = 0;
    int value = 0;

    extract_data_arena(arena, head->index + 2, 1, (char *)&reg);
    if (reg == 0 || reg >= REG_NUMBER) {
        head->carry = false;
        return;
    }
    extract_data_arena(arena,
        (head->index + 3) % MEM_SIZE, 2, (char *)&indirect);
    extract_data_arena(arena,
        head->index + indirect % IDX_MOD, REG_SIZE, (char *)&value);
    head->registers[reg - 1] = value;
}

void instruction_load(head_t *head, char *arena, parameters_t *)
{
    unsigned char coding_byte = arena[(head->index + 1) % MEM_SIZE];
    char *binary_code = dec_to_bin(coding_byte);
    int tmp = 0;

    if (search_byte_size(binary_code, &tmp) == DIR_SIZE_FILE) {
        put_dir_in_reg(head, arena);
        head->index = (head->index + 7) % MEM_SIZE;
    } else {
        put_indir_in_reg(head, arena);
        head->index = (head->index + 4) % MEM_SIZE;
    }
    head->carry = true;
    free(binary_code);
}
