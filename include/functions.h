/*
** EPITECH PROJECT, 2024
** functions
** File description:
** functions prototypes for corewar
*/

#pragma once

    #include <stdbool.h>
    #include "parameters.h"
    #include "arena.h"

int corewar(char **);

void print_help(void);

//parameters
parameters_t *get_parameters(char **argv);
void free_parameters(parameters_t *params);
void free_arena(arena_t *arena);
bool set_champions_numbers(champion_t **champions);
void init_champion_address(parameters_t *parameters);

arena_t *init_arena(parameters_t *);
void print_arena(arena_t *);

void push_front_head(head_t **list, head_t *to_push);
bool handle_wait(parameters_t *parameters, char *arena, head_t **heads);
void start_fight(parameters_t *parameters, char *arena, head_t **heads);

char *dec_to_bin(int nb);
