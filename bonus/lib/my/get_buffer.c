/*
** EPITECH PROJECT, 2024
** get buffer of a file
** File description:
** get buffer
*/

#include <stddef.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "lib.h"

static ssize_t get_size(char const *const path)
{
    struct stat sb = {0};

    if (stat(path, &sb) == -1) {
        my_puterr(path);
        my_puterr(": No such file or directory\n");
        return -1;
    }
    return sb.st_size;
}

char *get_buffer(char const *const path)
{
    ssize_t size = get_size(path);
    char *buffer = NULL;
    FILE *fd = NULL;

    if (size == -1)
        return NULL;
    fd = fopen(path, "r");
    if (fd == NULL)
        return NULL;
    buffer = malloc(sizeof(char) * (size + 1));
    if (buffer == NULL) {
        fclose(fd);
        return NULL;
    }
    fread(buffer, sizeof(char), size, fd);
    buffer[size] = '\0';
    fclose(fd);
    return buffer;
}
