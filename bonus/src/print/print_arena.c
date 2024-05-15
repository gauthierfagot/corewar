/*
** EPITECH PROJECT, 2024
** print arena
** File description:
** display arena for -dump
*/

#include <stdbool.h>
#include <ncurses.h>
#include <curses.h>
#include "arena.h"
#include "op.h"

static void put_exa_didgit(int i)
{
    if (i < 10) {
        printw("%d", i);
    } else {
        printw("%c", 'a' + (i - 10));
    }
}

static void print_exa(unsigned char number)
{
    if (number == 0) {
        printw("..");
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
        attron(A_REVERSE);
        return true;
    }
    return colorize_heads(&(*heads)->next, index);
}

void print_arena(arena_t *arena)
{
    int counter = 0;

    clear();
    for (int i = 0; i < MEM_SIZE; ++i) {
        if (colorize_heads(arena->heads, i)) {
            print_exa(arena->arena[i]);
            attroff(A_REVERSE);
        } else {
            print_exa(arena->arena[i]);
        }
        printw(" ");
        counter += 3;
        if (((counter + 3) >= COLS)) {
            printw("\n");
            counter = 0;
        }
    }
    refresh();
}
