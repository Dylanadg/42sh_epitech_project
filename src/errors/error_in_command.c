/*
** EPITECH PROJECT, 2024
** error_in_command.c
** File description:
** error_in_command
*/

#include "mysh.h"
#include "macros.h"

bool common_command_failed(char **command_array, char *command_path,
    char **env_array)
{
    if (command_array != NULL
    && error_in_command(command_array[0], command_path) != SUCCESS) {
        free_array(command_array);
        free_array(env_array);
        free(command_path);
        return true;
    }
    return false;
}
