/*
** EPITECH PROJECT, 2024
** wait handle
** File description:
** wiat
*/

#include <stdbool.h>
#include "arena.h"
#include "parameters.h"
#include "functions.h"

bool handle_wait(parameters_t *parameters, char *arena, head_t **heads)
{
    if ((*heads)->wait_cycle > 0) {
        (*heads)->wait_cycle -= 1;
        start_fight(parameters, arena, &(*heads)->next);
        return true;
    } else if ((*heads)->wait_cycle == 0) {
        (*heads)->instruction(*heads, arena, parameters);
        (*heads)->wait_cycle -= 1;
        start_fight(parameters, arena, &(*heads)->next);
        return true;
    }
    return false;
}
