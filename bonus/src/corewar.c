/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** fightiiiiiing
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include "macros.h"
#include "parameters.h"
#include "functions.h"
#include "arena.h"
#include "op.h"
#include "instructions.h"
#include "mini_printf.h"
#include "libmy.h"

static int count_alive_champs(parameters_t *parameters)
{
    int count = 0;

    for (int i = 0; parameters->champions[i] != NULL; ++i) {
        if (parameters->champions[i]->alive)
            ++count;
    }
    return count;
}

static void update_lives(parameters_t *parameters)
{
    for (int i = 0; parameters->champions[i] != NULL; ++i) {
        parameters->champions[i]->last_alive += 1;
    }
    if (parameters->live_counter > NBR_LIVE) {
        parameters->cycles -= CYCLE_DELTA;
        parameters->live_counter -= NBR_LIVE;
    }
}

static void print_won(head_t *winner, parameters_t *parameters)
{
    for (int i = 0; parameters->champions[i] != NULL; ++i) {
        if (parameters->champions[i]->number == winner->number) {
            mini_printf("The player %d (%s) has won.\n",
                parameters->champions[i]->number,
                parameters->champions[i]->name);
        }
    }
}

static void display_waiting_screen(void)
{
    char *buffer = get_buffer(WAITING_SCREEN);
    char **logo = NULL;

    if (buffer == NULL)
        return;
    logo = format_line(buffer, "\n", "");
    free(buffer);
    if (logo == NULL)
        return;
    attron(COLOR_PAIR(6));
    for (int i = 0; logo[i] != NULL; ++i)
        mvprintw((LINES / 4) + i, (COLS - my_strlen(logo[i])) / 2,
        "%s\n", logo[i]);
    attroff(COLOR_PAIR(6));
    mvprintw((LINES / 4) + my_arraylen(logo) + 5,
        (COLS - my_strlen(WAITING_MESSAGE)) / 2, "%s\n", WAITING_MESSAGE);
    refresh();
    getch();
    free_array(logo);
}

static bool set_window_parameters()
{
    curs_set(0);
    if (!has_colors()) {
        mini_printf("your terminal doesn't support colors\n");
        return false;
    }
    if (start_color() == ERR)
        return false;
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_WHITE, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_RED, 0);
    return true;
}

static bool launch_arena(parameters_t *parameters)
{
    arena_t *arena = init_arena(parameters);

    if (arena == NULL)
        return false;
    initscr();
    if (!set_window_parameters()) {
        free_arena(arena);
        return false;
    }
    display_waiting_screen();
    timeout(0);
    for (int i = 0; count_alive_champs(parameters) > 1; i++) {
        start_fight(parameters, arena->arena, arena->heads);
        update_lives(parameters);
        if ((i + 1) % parameters->dump == 0)
            print_arena(arena, parameters, i);
        if (getch() == 'q')
            break;
    }
    endwin();
    if (*arena->heads != NULL)
        print_won(*arena->heads, parameters);
    else
        mini_printf("Everybody is dead... :(\n");
    free_arena(arena);
    return true;
}

int corewar(char **argv)
{
    parameters_t *parameters = get_parameters(argv);

    if (parameters == NULL)
        return ERROR;
    init_champion_address(parameters);
    if (!launch_arena(parameters)) {
        free_parameters(parameters);
        return ERROR;
    }
    free_parameters(parameters);
    return SUCCESS;
}
