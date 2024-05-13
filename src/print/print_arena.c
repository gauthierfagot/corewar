/*
** EPITECH PROJECT, 2024
** print arena
** File description:
** display arena for -dump
*/

#include <stdbool.h>
#include "arena.h"
#include "op.h"
#include "mini_printf.h"

static void put_exa_didgit(int i)
{
    if (i < 10) {
        mini_printf("%d", i);
    } else {
        mini_printf("%c", 'a' + (i - 10));
    }
}

static void print_exa(unsigned char number)
{
    if (number == 0) {
        my_putstr("..");
        return;
    }
    put_exa_didgit(number / 16);
    put_exa_didgit(number % 16);
}

static bool colorize_heads(head_t **heads, int index)
{
    if (*heads == NULL)
        return false;
    if ((*heads)->index == index) {
        mini_printf("\x1b[47m\x1b[30m");
        return true;
    }
    return colorize_heads(&(*heads)->next, index);
}

void print_arena(arena_t *arena)
{
    for (int i = 0; i < MEM_SIZE; ++i) {
        if (colorize_heads(arena->heads, i)) {
            print_exa(arena->arena[i]);
            mini_printf("\x1b[0m");
        } else {
            print_exa(arena->arena[i]);
        }
        my_putstr(" ");
    }
    my_putchar('\n');
}
