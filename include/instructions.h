/*
** EPITECH PROJECT, 2024
** instructoins
** File description:
** cor war instructions
*/

#pragma once

#include "arena.h"
#include "parameters.h"

void instruction_alive(head_t *, char *, parameters_t *);

static void (*INSTRUCTIONS[])(head_t *, char *, parameters_t *) = {
    instruction_alive,
};

static const int NB_OF_INSTRUCTIONS = sizeof(INSTRUCTIONS) / sizeof(void *);
