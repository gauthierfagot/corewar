/*
** EPITECH PROJECT, 2024
** print arena
** File description:
** display arena for -dump
*/

#include <stdbool.h>
#include <ncurses.h>
#include <curses.h>
#include <math.h>
#include "arena.h"
#include "op.h"
#include "libmy.h"

static void put_exa_didgit(int i, int line, int cols)
{
    if (i < 10) {
        mvprintw(line, ((COLS - (128 * 3)) / 2) + cols, "%d", i);
    } else {
        mvprintw(line, ((COLS - (128 * 3)) / 2) + cols, "%c", 'a' + (i - 10));
    }
}

static void print_exa(unsigned char number, int line, int cols)
{
    if (number == 0) {
        mvprintw(line, ((COLS - (128 * 3)) / 2) + cols, "..");
        return;
    }
    put_exa_didgit(number / 16, line, cols);
    put_exa_didgit(number % 16, line, cols + 1);
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

static size_t champions_alive_len(champion_t **champions)
{
    int len = 0;

    for (int i = 0; champions[i]; i++)
        if (champions[i]->alive)
            ++len;
    return len;
}

static void print_champ(champion_t *champion, int len, int current, int line)
{
    int cols = (((COLS) / (len + 1)) * current) - 10;

    mvprintw(line, cols, "/----------------\\");
    mvprintw(line + 1, cols, "| ");
    attron(COLOR_PAIR(champion->color));
    mvprintw(line + 1, cols + 2 + ((my_strlen(champion->name) > 14) ?
        0 : (14 - my_strlen(champion->name)) / 2), "%.14s", champion->name);
    attroff(COLOR_PAIR(champion->color));
    mvprintw(line + 1, cols + 16, " |");
    mvprintw(line + 2, cols, "|                |");
    mvprintw(line + 3, cols, "|   last alive   |");
    mvprintw(line + 4, cols, "| ");
    mvprintw(line + 4, cols + (17 - (int)(log10(champion->last_alive))) / 2,
        "%d", champion->last_alive);
    mvprintw(line + 4, cols + 16, " |");
    mvprintw(line + 5, cols, "\\----------------/");
}

static void print_champions_name(parameters_t *parameters, int line, int cycles)
{
    int len = champions_alive_len(parameters->champions);
    int current = 1;

    for (int i = 0;parameters->champions[i] != NULL; ++i) {
        if (parameters->champions[i]->alive) {
            print_champ(parameters->champions[i], len, current, line);
            ++current;
        }
    }
    mvprintw(line + 8, (COLS - 19) /
                2, "Number of cycles: %d", cycles);
    mvprintw(line + 10, (COLS - 19) /
                2, "Number of cycles to die: %d", parameters->cycles);
    mvprintw(line + 12, (COLS - 16) / 2, "PRESS Q TO QUIT");
}

void print_arena(arena_t *arena, parameters_t *parameters, int cycles)
{
    int line = 0;
    int cols = 0;

    clear();
    for (int i = 0; i < MEM_SIZE; ++i) {
        if (colorize_heads(arena->heads, i)) {
            print_exa(arena->arena[i].byte, line, cols);
            attroff(COLOR_PAIR(5));
        } else {
            if (arena->arena[i].color != -1) {
                attron(COLOR_PAIR(arena->arena[i].color));
                print_exa(arena->arena[i].byte, line, cols);
                attroff(COLOR_PAIR(arena->arena[i].color));
            } else
                print_exa(arena->arena[i].byte, line, cols);
        }
        if ((i + 1) % 128 == 0) {
            line += 1;
            cols = 0;
        } else {
            cols += 3;
        }
    }
    line += 2;
    print_champions_name(parameters, line, cycles);
    refresh();
}
