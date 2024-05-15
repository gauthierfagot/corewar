/*
** EPITECH PROJECT, 2024
** check flag
** File description:
** check flag
*/

#include <stdbool.h>
#include "libmy.h"

bool check_dump(char ***arg)
{
    if (my_strcmp(**arg, "-dump") == 0) {
        *arg += 1;
        return true;
    }
    return false;
}

bool check_prog_number(char ***arg)
{
    if (my_strcmp(**arg, "-n") == 0) {
        *arg += 1;
        return true;
    }
    return false;
}

bool check_load(char ***arg)
{
    if (my_strcmp(**arg, "-a") == 0) {
        *arg += 1;
        return true;
    }
    return false;
}

bool default_case(char ***arg)
{
    (void)arg;
    return true;
}
