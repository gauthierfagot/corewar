/*
** EPITECH PROJECT, 2024
** conv_coding_byte
** File description:
** conv_coding_byte
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "op.h"
#include "libmy.h"
#include "arena.h"

int bin_len(int nb)
{
    int n = 0;

    while (nb > 0) {
        nb = nb / 2;
        n ++;
    }
    return n;
}

char *dec_to_bin(int nb)
{
    char *bin = malloc(sizeof(char) * (8));

    for (int i = 0; i < 8; ++i) {
        bin[7 - i] = (nb % 2) + '0';
        nb = nb / 2;
    }
    return bin;
}

void print_n_bytes_in_arena(char *arena, int index,
    int byte_size, char *to_print)
{
    for (int i = 0; i < byte_size; i++) {
        arena[(index + i) % MEM_SIZE] = to_print[byte_size - 1 - i];
    }
}

void extract_data_arena(char *arena, int index, int byte_size, char *result)
{
    int tmp_size = byte_size - 1;

    if (byte_size > 4 || index + byte_size >= MEM_SIZE)
        return;
    for (int i = 0; i < byte_size; ++i) {
        result[tmp_size] = arena[index];
        ++index;
        --tmp_size;
    }
}


int search_byte_size(char *coding_byte, int *index)
{
    if (*index >= (MAX_ARGS_NUMBER * 2)) {
        return 0;
    }
    if (coding_byte[*index] == '0' && coding_byte[*index + 1] == '1') {
        *index = *index + 2;
        return REG_SIZE_FILE;
    }
    if (coding_byte[*index] == '1' && coding_byte[*index + 1] == '0'){
        *index = *index + 2;
        return DIR_SIZE_FILE;
    }
    if (coding_byte[*index] == '1' && coding_byte[*index + 1] == '1') {
        *index = *index + 2;
        return IND_SIZE_FILE;
    }
    return 0;
}

void extract_arguments_size(int nb_of_args,
    char *arena, head_t *head, int *args)
{
    char *binary_code = dec_to_bin((uint8_t)arena[(head->index + 1) % MEM_SIZE]);
    int tmp = 0;

    for (int i = 0; i < nb_of_args; ++i) {
        args[i] = search_byte_size(binary_code, &tmp);
    }
    free(binary_code);
}