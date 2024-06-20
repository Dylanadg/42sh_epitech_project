/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** has_redirection
*/

#include "mysh.h"

bool is_char_redir(char c)
{
    if (c == '>' || c == '<' || c == ';' || c == '|' || c == '&')
        return true;
    return false;
}

bool has_redirection(const char *string)
{
    if (string == NULL)
        return false;
    for (int i = 0; string[i] != '\0'; i++)
        if (is_char_redir(string[i]))
            return true;
    return false;
}
