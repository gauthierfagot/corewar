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
#include "libmy.h"

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
        attron(COLOR_PAIR(5));
        return true;
    }
    return colorize_heads(&(*heads)->next, index);
}

static void print_champions_name(parameters_t *parameters, int line, int cycles)
{
    for (int i = 0;parameters->champions[i] != NULL; ++i) {
        attron(COLOR_PAIR(parameters->champions[i]->color));
        if (parameters->champions[i]->alive == true) {
            mvprintw(line, (COLS - my_strlen(parameters->champions[i]->name)) /
                2, parameters->champions[i]->name);
            line += 2;
        }
        attroff(COLOR_PAIR(parameters->champions[i]->color));
    }
    mvprintw(line, (COLS - 19) /
                2, "Number of cycles: %d", cycles);
    mvprintw(line + 2, (COLS - 19) /
                2, "Number of cycles to die: %d", parameters->cycles);
    mvprintw(line + 4, (COLS - 16) / 2, "PRESS Q TO QUIT");
}

void print_arena(arena_t *arena, parameters_t *parameters, int cycles)
{
    int counter = 0;
    int line = 2;

    clear();
    for (int i = 0; i < MEM_SIZE; ++i) {
        if (colorize_heads(arena->heads, i)) {
            print_exa(arena->arena[i].byte);
            attroff(COLOR_PAIR(5));
        } else {
            if (arena->arena[i].color != -1) {
                attron(COLOR_PAIR(arena->arena[i].color));
                print_exa(arena->arena[i].byte);
                attroff(COLOR_PAIR(arena->arena[i].color));
            } else
                print_exa(arena->arena[i].byte);
        }
        printw(" ");
        counter += 3;
        if (((counter + 3) >= COLS)) {
            printw("\n");
            line += 1;
            counter = 0;
        }
    }
    print_champions_name(parameters, line, cycles);
    refresh();
}
