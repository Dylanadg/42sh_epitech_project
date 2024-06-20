/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** is_in_current_dir
*/

#include "mysh.h"

bool is_in_current_dir(const char *command)
{
    bool starts_with_slash = is_a_binary(command);

    if (command == NULL)
        return false;
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '/' && !starts_with_slash)
            return false;
    }
    return true;
}
