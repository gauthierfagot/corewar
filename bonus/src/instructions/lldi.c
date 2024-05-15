/*
** EPITECH PROJECT, 2024
** lldi
** File description:
** lldi
*/

#include "arena.h"
#include "parameters.h"
#include "mini_printf.h"
#include "functions.h"

static bool load_index(head_t *head, byte_t *arena, int *args)
{
    int first = 0;
    int second = 0;
    unsigned char third = 0;
    int first_adress = 0;
    int second_adress = 0;

    extract_data_arena(arena, head->index + 2, args[0], (char *)&first);
    extract_data_arena(arena, head->index + 2 + args[0], args[1],
        (char *)&second);
    extract_data_arena(arena,
        head->index + 2 + args[0] + args[1], args[2], (char *)&second);
    if (third == 0 || third > REG_NUMBER)
        return false;
    extract_data_arena(arena, (head->index + first) % MEM_SIZE,
        REG_SIZE, (char *)&first_adress);
    second_adress = first_adress + second;
    extract_data_arena(arena, (head->index + second_adress) %
        MEM_SIZE, 4, (char *)&head->registers[third - 1]);
    return true;
}

void instruction_lldi(head_t *head, byte_t *arena, parameters_t *)
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
