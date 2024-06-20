/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** is_redirection
*/

#include "redirection.h"
#include "mysh.h"
#include "macros.h"

bool is_redirection(const char *str)
{
    if (str == NULL)
        return false;
    for (int i = 0; i != NB_SEP; i++)
        if (my_strcmp(str, redirections[i].sep) == 0)
            return true;
    return false;
}

bool is_final_command(const char *command)
{
    if (command == NULL || is_multiple_semicolon(command))
        return true;
    return false;
}

bool is_semicolon(const char *str)
{
    if (my_strcmp(str, redirections[SEMICOLON].sep) == SIMILAR)
        return true;
    return false;
}

bool is_multiple_semicolon(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] != ';')
            return false;
    }
    return true;
}
