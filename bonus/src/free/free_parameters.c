/*
** EPITECH PROJECT, 2024
** free params
** File description:
** free the params
*/

#include <stdlib.h>
#include "parameters.h"

void free_parameters(parameters_t *params)
{
    if (params == NULL)
        return;
    if (!params->champions) {
        free(params);
        return;
    }
    for (int i = 0; params->champions[i]; ++i) {
        if (params->champions[i]->path)
            free(params->champions[i]->path);
        free(params->champions[i]);
    }
    free(params->champions);
    free(params);
}
