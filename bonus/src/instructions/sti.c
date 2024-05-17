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

static int get_value(int args_size, head_t *head,
    int parameter, byte_t *arena)
{
    int tmp = 0;

    if (args_size == REG_SIZE_FILE) {
        return head->registers[parameter - 1];
    }
    if (args_size == IND_SIZE_FILE) {
        extract_data_arena(arena, head->index + parameter, 4, (char *)&tmp);
        return tmp;
    }
    return parameter;
}

static bool check_registers(int *args, int first, int second, int third)
{
    if (args[0] == REG_SIZE_FILE && (first <= 0 || first > REG_NUMBER))
        return false;
    if (args[1] == REG_SIZE_FILE && (second <= 0 || second > REG_NUMBER))
        return false;
    if (args[2] == REG_SIZE_FILE && (third <= 0 || third > REG_NUMBER))
        return false;
    return true;
}

static bool store_index(head_t *head, byte_t *arena, int *args)
{
    int first = 0;
    int second = 0;
    int third = 0;

    extract_data_arena(arena, head->index + 2, args[0], (char *)&first);
    extract_data_arena(arena, head->index + 2 + (args[0]),
        args[1] == 4 ? 2 : args[1], (char *)&second);
    extract_data_arena(arena, head->index + 2 + (args[0]) + (args[1] == 4 ?
        2 : args[1]), (args[2] == 4 ? 2 : args[2]), (char *)&third);
    if (!check_registers(args, first, second, third))
        return false;
    first = head->registers[first - 1];
    second = get_value(args[1], head, second, arena);
    third = get_value(args[2], head, third, arena);
    print_n_bytes_in_arena(arena, (head->index +
        (second + third) % IDX_MOD) % MEM_SIZE, 4, (char *)&first, head->color);
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
        if (!store_index(head, arena, args)) {
            head->carry = false;
        } else {
            head->carry = true;
        }
        args[1] = (args[1] == 4) ? 2 : args[1];
        args[2] = (args[2] == 4) ? 2 : args[2];
    }
    head->index = (head->index + 2 + args[0] + args[1] + args[2]) %
            MEM_SIZE;
}
