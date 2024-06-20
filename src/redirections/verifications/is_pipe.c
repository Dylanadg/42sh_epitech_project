/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** is_pipe
*/

#include "redirection.h"

bool is_pipe(const char *str)
{
    if (my_strcmp(str, redirections[PIPE].sep) == 0)
        return true;
    return false;
}
