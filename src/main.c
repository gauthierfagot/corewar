/*
** EPITECH PROJECT, 2024
** main
** File description:
** main for corewar
*/

#include "macros.h"
#include "libmy.h"
#include "functions.h"

int main(int argc, char **argv)
{
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        print_help();
        return SUCCESS;
    }
    return corewar(argv);
}
