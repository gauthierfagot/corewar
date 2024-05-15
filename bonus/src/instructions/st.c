/*
** EPITECH PROJECT, 2024
** st
** File description:
** st
*/

#include "arena.h"
#include "parameters.h"
#include "mini_printf.h"
#include "functions.h"
#include "op.h"

static void store_register(head_t *head, byte_t *arena)
{
    unsigned char first = arena[head->index + 2].byte;
    unsigned char second = arena[head->index + 3].byte;

    if ((first == 0 || second == 0) ||
        first > REG_NUMBER || second > REG_NUMBER)
        return;
    head->registers[second - 1] = head->registers[first - 1];
}

static void print_value(head_t *head, byte_t *arena)
{
    int direct = 0;
    unsigned char first = arena[(head->index + 2) % MEM_SIZE].byte;

    if (first == 0 || first > REG_NUMBER)
        return;
    extract_data_arena(arena, head->index + 3, 4, (char *)&direct);
    print_n_bytes_in_arena(arena, head->index + direct % IDX_MOD, 4,
        (char *)&head->registers[first - 1]);
}

void instruction_st(head_t *head, byte_t *arena, parameters_t *)
{
    unsigned char coding_byte = arena[head->index + 1].byte;
    char binary_code[8] = {0};
    int tmp = 0;

    dec_to_bin(coding_byte, binary_code);
    search_byte_size(binary_code, &tmp);
    if (search_byte_size(binary_code, &tmp) == DIR_SIZE_FILE) {
        print_value(head, arena);
        head->index = (head->index + 7) % MEM_SIZE;
    } else {
        store_register(head, arena);
        head->index = (head->index + 4) % MEM_SIZE;
    }
}
