/*
** EPITECH PROJECT, 2024
** conv_coding_byte
** File description:
** conv_coding_byte
*/

#include <stdlib.h>
#include <stdbool.h>
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
    int n = bin_len(nb);
    char *bin = malloc(sizeof(char) * (n + 1));

    bin[n] = '\0';
    while (nb > 0) {
        bin[n - 1] = (nb % 2) + '0';
        nb = nb / 2;
        n --;
    }
    return bin;
}

int search_byte_size(char *coding_byte, int *index)
{
    if (my_strlen(coding_byte) != (MAX_ARGS_NUMBER * 2) ||
    *index >= (MAX_ARGS_NUMBER * 2))
        return 0;
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
