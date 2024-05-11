/*
** EPITECH PROJECT, 2024
** init parameters
** File description:
** init
*/

#include <stdlib.h>
#include "parameters.h"
#include "op.h"
#include "libmy.h"

bool set_dump(parameters_t *parameters, char *data, int *, int *)
{
    if (data == NULL) {
        my_puterr("-d: missing number. try -h for help\n");
        return false;
    }
    if (parameters->dump != - 1) {
        my_puterr("sry you cant set 2 dump cycles :(\n");
        return false;
    }
    if (!is_number(data)) {
        my_puterr("-d: data is not a number. try -h for help\n");
        return false;
    }
    parameters->dump = str_to_int(data);
    return true;
}

bool set_prog_number(parameters_t *, char *data, int *prog, int *)
{
    if (data == NULL) {
        my_puterr("-n: missing number. try -h for help\n");
        return false;
    }
    if (!is_number(data)) {
        my_puterr("-n: data is not a number. try -h for help\n");
        return false;
    }
    *prog = str_to_int(data);
    return true;
}

bool set_load(parameters_t *, char *data, int *, int *load)
{
    if (data == NULL)
        if (data == NULL) {
        my_puterr("-a: missing number. try -h for help\n");
        return false;
    }
    if (!is_number(data)) {
        my_puterr("-a: data is not a number. try -h for help\n");
        return false;
    }
    *load = str_to_int(data) % MEM_SIZE;
    return true;
}

static size_t champions_len(champion_t **champions)
{
    int len = 0;

    while (champions[len])
        ++len;
    return len;
}

bool set_path(parameters_t *parameters, char *path, int *prog, int *load)
{
    champion_t *new = malloc(sizeof(champion_t));
    size_t len = champions_len(parameters->champions);

    if (new == NULL)
        return false;
    new->load_adress = *load;
    new->number = *prog;
    new->path = my_strdup(path);
    parameters->champions = realloc(parameters->champions,
        sizeof(champion_t *) * (len + 2));
    if (parameters->champions == NULL)
        return false;
    parameters->champions[len] = new;
    parameters->champions[len + 1] = NULL;
    parameters->champions[len]->last_alive = 0;
    parameters->champions[len]->alive = true;
    *load = -1;
    *prog = -1;
    return true;
}
