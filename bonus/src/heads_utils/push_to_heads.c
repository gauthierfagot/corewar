/*
** EPITECH PROJECT, 2024
** push to head
** File description:
** push a head in front of the list
*/

#include "arena.h"

void push_front_head(head_t **list, head_t *to_push)
{
    to_push->next = *list;
    *list = to_push;
}

void push_index_head(head_t *head, head_t *to_push)
{
    to_push->next = head->next;
    head->next = to_push;
}
