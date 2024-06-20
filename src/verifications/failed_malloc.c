/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** failed_malloc
*/

#include "mysh.h"

bool both_malloc_failed(char **first, char **second)
{
    bool failed = false;

    if (first == NULL || second == NULL)
        failed = true;
    if (failed && first != NULL)
        free_array(first);
    if (failed && second != NULL)
        free_array(second);
    return (failed ? true : false);
}
