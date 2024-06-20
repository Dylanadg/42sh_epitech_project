/*
** EPITECH PROJECT, 2024
** add.c
** File description:
** adding an element to a list
*/

#include "mysh.h"

list_t *create_node(char *var, char *value)
{
    list_t *new_node = NULL;

    if (var == NULL)
        return NULL;
    new_node = malloc(sizeof(list_t));
    if (new_node == NULL)
        return NULL;
    new_node->var = my_strdup(var);
    new_node->value = my_strdup(value);
    new_node->next = NULL;
    return new_node;
}
