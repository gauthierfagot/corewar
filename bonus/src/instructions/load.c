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

static bool put_dir_in_reg(head_t *head, char *arena)
{
    unsigned char reg = 0;
    int direct = 0;

    extract_data_arena(arena, head->index + 2, 4, (char *)&direct);
    extract_data_arena(arena,
        (head->index + 6) % MEM_SIZE, 1, (char *)&reg);
    if (reg == 0 || reg > REG_NUMBER) {
        head->carry = false;
        return false;
    }
    head->registers[reg - 1] = direct;
    return true;
}

static bool put_indir_in_reg(head_t *head, char *arena)
{
    unsigned char reg = 0;
    __int16_t indirect = 0;
    int value = 0;

    extract_data_arena(arena, head->index + 2, 2, (char *)&indirect);
    extract_data_arena(arena,
        (head->index + 4) % MEM_SIZE, 1, (char *)&reg);
    if (reg == 0 || reg > REG_NUMBER) {
        head->carry = false;
        return false;
    }
    extract_data_arena(arena, (head->index + indirect % IDX_MOD) %
        MEM_SIZE, REG_SIZE, (char *)&value);
    head->registers[reg - 1] = value;
    return true;
}

void instruction_load(head_t *head, char *arena, parameters_t *)
{
    unsigned char coding_byte = arena[(head->index + 1) % MEM_SIZE];
    char binary_code[8] = {0};
    int tmp = 0;

    dec_to_bin(coding_byte, binary_code);
    if (search_byte_size(binary_code, &tmp) == DIR_SIZE_FILE) {
        if (!put_dir_in_reg(head, arena))
            head->carry = false;
        else
            head->carry = true;
        head->index = (head->index + 7) % MEM_SIZE;
    } else {
        if (!put_indir_in_reg(head, arena))
            head->carry = false;
        else
            head->carry = true;
        head->index = (head->index + 5) % MEM_SIZE;
    }
}
