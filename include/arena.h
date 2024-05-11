/*
** EPITECH PROJECT, 2024
** arena
** File description:
** arena
*/

#pragma once

#include <stddef.h>
#include "op.h"

typedef struct head_s {
    int number;
    char name[PROG_NAME_LENGTH + 1];
    int index;
    size_t wait_cycle;
    struct head_s *next;
}head_t;

typedef struct arena_s {
    char *arena;
    head_t **heads;
}arena_t;