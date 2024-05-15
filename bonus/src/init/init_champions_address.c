/*
** EPITECH PROJECT, 2024
** init_champions_arena
** File description:
** init_champions_arena
*/

#include "macros.h"
#include "parameters.h"
#include "functions.h"
#include "op.h"

static void swap_champions(champion_t **a, champion_t **b)
{
    champion_t *c = NULL;

    c = *a;
    *a = *b;
    *b = c;
}

static void sort_champions(champion_t **champions, int nb_champions)
{
    for (int i = 0; i < nb_champions; ++i) {
        if (i + 1 < nb_champions && (champions[i + 1]->load_address
        < champions[i]->load_address)) {
            swap_champions(&champions[i], &champions[i + 1]);
            i = 0;
        }
    }
}

static void compare_last_gape(int tmp_address, int *best_gap, int *index)
{
    if (MEM_SIZE - tmp_address > *best_gap) {
        *best_gap = MEM_SIZE - tmp_address;
        *index = MEM_SIZE;
    }
}

static int search_best_address(champion_t **champions, int nb_champions)
{
    int best_gap = 0;
    int tmp_address = 0;
    int index = 0;

    for (int i = 0; i < nb_champions; ++i) {
        if (champions[i]->load_address < 0)
            continue;
        if (best_gap == 0) {
            best_gap = champions[i]->load_address;
            index = champions[i]->load_address;
        }
        if (best_gap != 0 && champions[i]->load_address - tmp_address
        > best_gap) {
            best_gap = champions[i]->load_address - tmp_address;
            index = champions[i]->load_address;
        }
        tmp_address = champions[i]->load_address;
    }
    compare_last_gape(tmp_address, &best_gap, &index);
    return index - (best_gap / 3);
}

static void find_address(parameters_t *parameters, int i)
{
    int j = 0;

    sort_champions(parameters->champions, i);
    while (parameters->champions[j] != NULL) {
        if (parameters->champions[j]->load_address == -1) {
            parameters->champions[j]->load_address =
                search_best_address(parameters->champions, i);
            sort_champions(parameters->champions, i);
            j = 0;
            continue;
        }
        ++j;
    }
}

static void init_all_address(champion_t **champions, int nb_champions)
{
    int address = MEM_SIZE / (nb_champions + 1);

    for (int i = 0; i < nb_champions; ++i)
        champions[i]->load_address = address * (i + 1);
}

void init_champion_address(parameters_t *parameters)
{
    int champ_with_address = 0;
    int i = 0;

    while (parameters->champions[i] != NULL) {
        if (parameters->champions[i]->load_address != -1) {
            parameters->champions[i]->load_address %= MEM_SIZE;
            ++champ_with_address;
        }
        ++i;
    }
    if (champ_with_address == 0)
        init_all_address(parameters->champions, i);
    else if (champ_with_address != i)
        find_address(parameters, i);
}
