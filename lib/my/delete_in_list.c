/*
** EPITECH PROJECT, 2024
** delete_in_list.c
** File description:
** deleting in element in list
*/

#include "mysh.h"

int delete_node(list_t *list)
{
    list_t *tmp = list->next;

    list->next = list->next->next;
    free(tmp);
    return 0;
}

int delete_in_list(list_t **list, char *var)
{
    list_t *tmp = NULL;

    if (list == NULL || *list == NULL || var == NULL)
        return 0;
    tmp = *list;
    if (my_strcmp(var, (*list)->var) == 0) {
        *list = (*list)->next;
        free(tmp);
        return 0;
    }
    while (tmp->next != NULL) {
        if (my_strcmp(var, tmp->next->var) == 0)
            return delete_node(tmp);
        tmp = tmp->next;
    }
    return 0;
}
