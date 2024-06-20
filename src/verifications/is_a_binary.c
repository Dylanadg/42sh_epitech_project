/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** is_a_binary
*/

#include "mysh.h"

bool is_a_binary(const char *command)
{
    if (command == NULL)
        return false;
    if ((my_strlen(command) > 2 && command[0] == '.' && command[1] == '/')
    || (my_strlen(command) > 3 && command[0] == '.' && command[1] == '.'
    && command[2] == '/'))
        return true;
    return false;
}
