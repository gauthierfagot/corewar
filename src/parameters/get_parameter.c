/*
** EPITECH PROJECT, 2024
** get_parameters_data
** File description:
** get them
*/

#include <stdlib.h>
#include "parameters.h"
#include "libmy.h"
#include "get_parameter.h"
#include "functions.h"
#include "op.h"

static parameters_t *init_parameters(void)
{
    parameters_t *new = malloc(sizeof(parameters_t));

    if (new == NULL)
        return NULL;
    new->arena = malloc(sizeof(char) * MEM_SIZE);
    if (new->arena == NULL) {
        free(new);
        return NULL;
    }
    for (int i = 0; i < MEM_SIZE; ++i)
        new->arena[i] = 0;
    new->dump = -1;
    new->champions = malloc(sizeof(champion_t *));
    if (new->champions == NULL) {
        free(new->arena);
        free(new);
        return NULL;
    }
    new->champions[0] = NULL;
    return new;
}

static bool get_parameters_data(parameters_t *parameters,
    char **args, int prog_number, int adress)
{
    bool tmp = false;

    if (*args == NULL)
        return true;
    for (size_t i = 0; i < INIT_PARAMS_SIZE; ++i) {
        if (INIT_PARAMS[i].check(&args)) {
            tmp = INIT_PARAMS[i].init(parameters,
                *args, &prog_number, &adress);
            return (tmp == false) ? false :
                get_parameters_data(parameters,
                    args + 1, prog_number, adress);
        }
    }
    return true;
}

static bool set_parameters(parameters_t *parameters)
{
    if (!set_champions_numbers(parameters->champions))
        return false;
    return true;
}

parameters_t *get_parameters(char **argv)
{
    parameters_t *parameters = init_parameters();

    if (parameters == NULL)
        return NULL;
    if (!get_parameters_data(parameters, (argv + 1), -1, -1)) {
        free_parameters(parameters);
        return NULL;
    }
    if (!set_parameters(parameters)) {
        free_parameters(parameters);
        return NULL;
    }
    return parameters;
}
