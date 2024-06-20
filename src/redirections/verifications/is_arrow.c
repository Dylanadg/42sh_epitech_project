/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** is_arrow
*/

#include "library.h"
#include "redirection.h"

bool is_right_arrow(const char *str)
{
    if (my_strcmp(str, redirections[RIGHT_ARROW].sep) == 0)
        return true;
    return false;
}

bool is_left_arrow(const char *str)
{
    if (my_strcmp(str, redirections[LEFT_ARROW].sep) == 0)
        return true;
    return false;
}

bool is_arrow_redirection(const char *command)
{
    for (int i = AND_AND; i != NB_SEP; i++)
        if (my_strcmp(command, redirections[i].sep) == 0)
            return true;
    return false;
}
