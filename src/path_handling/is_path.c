/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** is_path
*/

#include "library.h"

bool is_path(const char *env_line)
{
    if (my_strlen(env_line) >= 4 &&
    my_strncmp(env_line, "PATH", 4) == 0)
        return true;
    return false;
}
