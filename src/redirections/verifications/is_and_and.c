/*
** EPITECH PROJECT, 2024
** B-PSU-200-PAR-2-1-42sh-leonart.heurteux
** File description:
** is_&&
*/

#include <string.h>
#include "redirection.h"

bool is_and_redir(const char *command)
{
    if (command == NULL)
        return false;
    for (size_t i = 0; command[i] != '\0'; ++i) {
        if (command[i] != '&')
            return false;
    }
    return true;
}
