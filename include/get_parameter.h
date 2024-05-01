/*
** EPITECH PROJECT, 2024
** get parameters
** File description:
** get parameters
*/

#ifndef PARAMETERS_INIT_H
    #define PARAMETERS_INIT_H

    #include <stdbool.h>
    #include "parameters.h"

typedef struct init_params_s {
    bool (*check)(char ***);
    bool (*init)(parameters_t *, char *, int *, int *);
}init_params_t;

bool check_dump(char ***arg);
bool check_prog_number(char ***arg);
bool check_load(char ***arg);
bool default_case(char ***arg);

bool set_dump(parameters_t *, char *, int *, int *);
bool set_prog_number(parameters_t *, char *, int *, int *);
bool set_load(parameters_t *, char *, int *, int *);
bool set_path(parameters_t *, char *, int *, int *);

static const init_params_t INIT_PARAMS[] = {
    {check_dump, set_dump},
    {check_prog_number, set_prog_number},
    {check_load, set_load},
    {default_case, set_path},
};

static const size_t INIT_PARAMS_SIZE =
sizeof(INIT_PARAMS) / sizeof(init_params_t);

#endif
