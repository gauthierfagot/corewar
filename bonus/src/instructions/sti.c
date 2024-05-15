/*
** EPITECH PROJECT, 2024
** sti
** File description:
** sti
*/

#include "arena.h"
#include "parameters.h"
#include "mini_printf.h"
#include "functions.h"

static bool check_registers(unsigned char first,
    int second, int third, int *args)
{
    if (first == 0 || first > REG_NUMBER)
        return false;
    if (args[1] == 1 && (second == 0 || second > REG_NUMBER))
        return false;
    if (args[2] == 1 && (third == 0 || third > REG_NUMBER))
        return false;
    return true;
}

static bool store_index(head_t *head, byte_t *arena, int *args)
{
    int first = 0;
    int second = 0;
    int third = 0;

    extract_data_arena(arena, head->index + 2, args[0], (char *)&first);
    extract_data_arena(arena, head->index + 2 + args[0], args[1],
        (char *)&second);
    extract_data_arena(arena,
        head->index + 2 + args[0] + args[1], args[2], (char *)&third);
    if (!check_registers(first, second, third, args))
        return false;
    first = head->registers[first - 1];
    second = (args[1] == 1) ? head->registers[second - 1] : second;
    third = (args[2] == 1) ? head->registers[third - 1] : third;
    print_n_bytes_in_arena(arena, (head->index +
        (second + third) % IDX_MOD) % MEM_SIZE, 4, (char *)&first);
    return true;
}

void instruction_sti(head_t *head, byte_t *arena, parameters_t *)
{
    int args[3] = {0};

    extract_arguments_size(3, arena, head, args);
    if (args[0] != 1 || args[2] == 0 || args[2] == 0 || args[2] == 2) {
        head->carry = false;
        args[1] = (args[1] == 4) ? 2 : args[1];
        args[2] = (args[2] == 4) ? 2 : args[2];
    } else {
        args[1] = (args[1] == 4) ? 2 : args[1];
        args[2] = (args[2] == 4) ? 2 : args[2];
        if (!store_index(head, arena, args)) {
            head->carry = false;
        } else {
            head->carry = true;
        }
    }
    head->index = (head->index + 2 + args[0] + args[1] + args[2]) %
            MEM_SIZE;
}
