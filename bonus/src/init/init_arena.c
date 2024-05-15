/*
** EPITECH PROJECT, 2024
** init arena
** File description:
** init the arena
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "arena.h"
#include "op.h"
#include "parameters.h"
#include "libmy.h"
#include "op.h"
#include "functions.h"

static uint32_t reverse_hex_32(uint32_t nb)
{
    uint32_t result = 0;

    result |= ((nb & 0xFF000000) >> 24) | ((nb & 0x00FF0000) >> 8) |
    ((nb & 0x0000FF00) << 8) | ((nb & 0x000000FF) << 24);
    return result;
}

static bool extract_header(FILE **file, champion_t *champion)
{
    int magic = 0;

    fread(&magic, sizeof(int), 1, *file);
    magic = reverse_hex_32(magic);
    if (magic != COREWAR_EXEC_MAGIC) {
        my_puterr("wrong binary error\n");
        return false;
    }
    fread(champion->name, PROG_NAME_LENGTH + 1, 1, *file);
    fseek(*file, 0, SEEK_SET);
    if (fseek(*file, sizeof(header_t), SEEK_CUR) == -1) {
        fclose(*file);
        return false;
    }
    return true;
}

static void init_base_infos(head_t *tmp, int address, champion_t *champion)
{
    tmp->index = address;
    tmp->number = champion->number;
    tmp->wait_cycle = -1;
    for (int i = 0; i < REG_NUMBER; ++i)
        tmp->registers[i] = 0;
    tmp->registers[0] = champion->number;
    tmp->carry = true;
}

static bool extract_infos(FILE *file, champion_t *champion, head_t *tmp)
{
    if (file == NULL) {
        my_puterr(champion->path);
        my_puterr(": no such file or directory.\n");
        free(tmp);
        fclose(file);
        return false;
    }
    if (!extract_header(&file, champion)) {
        free(tmp);
        fclose(file);
        return false;
    }
    return true;
}

static bool print_program_in_arena(byte_t *arena, champion_t *champion,
    head_t **heads)
{
    int address = champion->load_address;
    FILE *file = fopen(champion->path, "r");
    head_t *tmp = NULL;

    if (file == NULL)
        return false;
    tmp = malloc(sizeof(head_t));
    if (tmp == NULL) {
        fclose(file);
        return false;
    }
    if (!extract_infos(file, champion, tmp))
        return false;
    for (int i = 0;
        fread(&((arena + ((address + i) % MEM_SIZE))->byte),
        1, 1, file) > 0; ++i);
    fclose(file);
    init_base_infos(tmp, address, champion);
    push_front_head(heads, tmp);
    return true;
}

static head_t **init_heads(champion_t **champions, byte_t *arena)
{
    head_t **heads = malloc(sizeof(head_t *));

    if (heads == NULL)
        return NULL;
    *heads = NULL;
    for (int i = 0; champions[i]; ++i) {
        if (!print_program_in_arena(arena, champions[i], heads)) {
            free_heads(heads);
            free(heads);
            return NULL;
        }
    }
    return heads;
}

arena_t *init_arena(parameters_t *parameters)
{
    arena_t *arena = malloc(sizeof(arena_t));

    if (arena == NULL)
        return NULL;
    arena->arena = malloc(sizeof(byte_t) * MEM_SIZE);
    if (arena->arena == NULL) {
        free(arena);
        return NULL;
    }
    for (int i = 0; i < MEM_SIZE; ++i) {
        arena->arena[i].byte = 0;
        arena->arena[i].color = -1;
    }
    arena->heads = init_heads(parameters->champions, arena->arena);
    if (arena->heads == NULL) {
        free(arena->arena);
        free(arena);
        return NULL;
    }
    return arena;
}
