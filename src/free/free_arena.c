/*
** EPITECH PROJECT, 2024
** free arena
** File description:
** free
*/

#include <stdlib.h>
#include "arena.h"

void free_heads(head_t **heads)
{
    if (*heads == NULL)
        return;
    free_heads(&(*heads)->next);
    free(*heads);
}

void free_arena(arena_t *arena)
{
    free(arena->arena);
    free_heads(arena->heads);
    free(arena->heads);
    free(arena);
}
