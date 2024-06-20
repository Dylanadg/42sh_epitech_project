/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** my_array_to_str
*/

#include "mysh.h"

char *array_to_str(const char **array)
{
    char *string = NULL;
    size_t size = 0;

    if (array == NULL)
        return NULL;
    size = my_arraylen(array);
    for (size_t i = 0; array[i] != NULL; i++) {
        my_strcat_mod(&string, array[i]);
        if (i < size - 1)
            my_strcat_mod(&string, " ");
    }
    return string;
}
