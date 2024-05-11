/*
** EPITECH PROJECT, 2024
** instructoins
** File description:
** cor war instructions
*/

#pragma once

#include "arena.h"
#include "parameters.h"

static void (*INSTRUCTIONS[])(head_t *, char *, parameters_t *) = {

};

static const int NB_OF_INSTRUCTIONS = sizeof(INSTRUCTIONS) / sizeof(void *);