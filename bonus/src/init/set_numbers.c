/*
** EPITECH PROJECT, 2024
** set champions number
** File description:
** set numbers
*/

#include <stdbool.h>
#include "parameters.h"
#include "libmy.h"

static int set_default_number(champion_t **champions, int number)
{
    for (int i = 0; champions[i]; ++i) {
        if (number == champions[i]->number)
            return set_default_number(champions, number + 1);
    }
    return number;
}

static bool check_champion_number(champion_t **champions, int i)
{
    for (int j = 0; champions[j]; ++j) {
        if (j == i)
            continue;
        if (champions[i]->number == champions[j]->number) {
            my_puterr("2 champions can't have the same number\n");
            return false;
        }
    }
    return true;
}

static bool set_champions_number(champion_t **champions, int i)
{
    if (champions[i]->number == -1) {
        champions[i]->number = set_default_number(champions, 1);
    } else if (!check_champion_number(champions, i)) {
            return false;
    }
    return true;
}

bool set_champions_numbers(champion_t **champions)
{
    for (int i = 0; champions[i]; ++i) {
        if (!set_champions_number(champions, i))
            return false;
    }
    return true;
}
