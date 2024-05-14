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

static void store_register(head_t *head, char *arena)
{
    unsigned char first = arena[head->index + 2];
    unsigned char second = arena[head->index + 3];

    if ((first == 0 || second == 0) ||
        first >= REG_NUMBER || second >= REG_NUMBER)
        return;
    head->registers[second] = head->registers[first];
}

static void print_value(head_t *head, char *arena)
{
    int direct = 0;
    unsigned char first = arena[(head->index + 2) % MEM_SIZE];

    if (first == 0 || first >= REG_NUMBER)
        return;
    extract_data_arena(arena, head->index + 3, 4, (char *)&direct);
    print_n_bytes_in_arena(arena, (head->index + direct) % IDX_MOD, 4,
        (char *)&head->registers[first]);
}

void instruction_st(head_t *head, char *arena, parameters_t *)
{   
    unsigned char coding_byte = arena[head->index + 1];
    char *binary_code = dec_to_bin(coding_byte);
    int tmp = 0;

    search_byte_size(binary_code, &tmp);
    if (search_byte_size(binary_code, &tmp) == DIR_SIZE_FILE) {
        print_value(head, arena);
        head->index = (head->index + 7) % MEM_SIZE;
    } else {
        store_register(head, arena);
        head->index = (head->index + 4) % MEM_SIZE;
    }
    free(binary_code);
}
