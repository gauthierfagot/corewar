/*
** EPITECH PROJECT, 2024
** ldi
** File description:
** ldi
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

static bool check_registers(int *args, int arguments[3])
{
    if (args[0] == REG_SIZE_FILE &&
        (arguments[0] <= 0 || arguments[0] > REG_NUMBER))
        return false;
    if (args[1] == REG_SIZE_FILE &&
        (arguments[1] <= 0 || arguments[1] > REG_NUMBER))
        return false;
    if (args[2] == REG_SIZE_FILE &&
        (arguments[2] <= 0 || arguments[2] > REG_NUMBER))
        return false;
    return true;
}

static bool load_index(head_t *head, byte_t *arena, int *args)
{
    int arguments[3] = {0};
    int second_size = (args[1] == 4 ? 2 : args[1]);
    int s = 0;

    extract_data_arena(arena, head->index + 2, args[0],
        (char *)&arguments[0]);
    extract_data_arena(arena, head->index + 2 + (args[0] == 4 ? 2 : args[0]),
        args[1] == 4 ? 2 : args[1], (char *)&arguments[1]);
    extract_data_arena(arena, head->index + 2 + (args[0] == 4 ? 2 : args[0]) +
        second_size, (args[2] == 4 ? 2 : args[2]), (char *)&arguments[2]);
    if (!check_registers(args, arguments))
        return false;
    arguments[0] = get_value(args[0], head, arguments[0], arena);
    arguments[1] = get_value(args[1], head, arguments[1], arena);
    arguments[2] = get_value(args[2], head, arguments[2], arena);
    extract_data_arena(arena, (head->index + (arguments[0]) % IDX_MOD) %
        MEM_SIZE, 4, (char *)&s);
    extract_data_arena(arena, (head->index + (s + arguments[1]) % IDX_MOD) %
        MEM_SIZE, 4, (char *)&head->registers[arguments[2] - 1]);
    return true;
}

void instruction_ldi(head_t *head, byte_t *arena, parameters_t *)
{
    int args[3] = {0};

    extract_arguments_size(3, arena, head, args);
    if (args[0] == 0 || args[1] == 0 ||
        args[1] == 4 || args[2] != 1) {
        args[0] = (args[0] == 4) ? 2 : args[0];
        args[1] = (args[1] == 4) ? 2 : args[1];
        head->carry = false;
    } else {
        args[0] = (args[0] == 4) ? 2 : args[0];
        args[1] = (args[1] == 4) ? 2 : args[1];
        if (!load_index(head, arena, args)) {
            head->carry = false;
        } else {
            head->carry = true;
        }
    }
    head->index = (head->index + 2 + args[0] + args[1] + args[2]) %
        MEM_SIZE;
}
