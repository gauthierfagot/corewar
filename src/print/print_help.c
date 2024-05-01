/*
** EPITECH PROJECT, 2024
** print help
** File description:
** print help
*/

#include "mini_printf.h"
#include "libmy.h"
#include "macros.h"

bool print_help(void)
{
    char *buffer = get_buffer(HELP_FILE);

    if (buffer == NULL)
        return false;
    mini_printf(buffer);
    free(buffer);
    return true;
}
