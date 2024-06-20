/*
** EPITECH PROJECT, 2023
** free_all.c
** File description:
** free
*/

#include "mysh.h"

void free_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
    return;
}

void free_int_array(int **array, int limit)
{
    for (int i = 0; i != limit; i++)
        free(array[i]);
    free(array);
}

void free_list(list_t *list)
{
    list_t *tmp = list;

    while (list != NULL) {
        list = list->next;
        free(tmp->value);
        free(tmp->var);
        free(tmp);
        tmp = list;
    }
    return;
}
