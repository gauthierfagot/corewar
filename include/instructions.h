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
void instruction_load(head_t *, char *, parameters_t *);
void instruction_st(head_t *, char *, parameters_t *);
void instruction_add(head_t *, char *, parameters_t *);
void instruction_sub(head_t *, char *, parameters_t *);
void instruction_and(head_t *, char *, parameters_t *);
void instruction_or(head_t *, char *, parameters_t *);
void instruction_xor(head_t *, char *, parameters_t *);
void instruction_zjmp(head_t *, char *, parameters_t *);
void instruction_ldi(head_t *, char *, parameters_t *);
void instruction_sti(head_t *, char *, parameters_t *);
void instruction_fork(head_t *, char *, parameters_t *);
void instruction_lld(head_t *, char *, parameters_t *);
void instruction_lldi(head_t *, char *, parameters_t *);
void instruction_lfork(head_t *, char *, parameters_t *);
void instruction_aff(head_t *, char *, parameters_t *);

static void (*INSTRUCTIONS[])(head_t *, char *, parameters_t *) = {
    instruction_alive,
    instruction_load,
    instruction_st,
    instruction_add,
    instruction_sub,
    instruction_and,
    instruction_or,
    instruction_xor,
    instruction_zjmp,
    instruction_ldi,
    instruction_sti,
    instruction_fork,
    instruction_lld,
    instruction_lldi,
    instruction_lfork,
    instruction_aff,
};

static const int NB_OF_INSTRUCTIONS = sizeof(INSTRUCTIONS) / sizeof(void *);
