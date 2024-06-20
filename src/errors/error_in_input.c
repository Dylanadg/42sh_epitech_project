/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** error_in_input
*/

#include "mysh.h"
#include "macros.h"

int wrong_number_of_arguments(char *function, int len, int required)
{
    if (len == required)
        return RIGHT_SIZE;
    if (len < required)
        dprintf(2, "\033[0;31m%s: Too few arguments.\033[0m\n", function);
    if (len > required)
        dprintf(2, "\033[0;31m%s: Too many arguments.\033[0m\n", function);
    return WRONG_SIZE;
}

int command_not_found(const char *command)
{
    dprintf(2, "\033[0;31m%s: Command not found.\033[0m\n", command);
    return SHELL_ERROR;
}

int permission_denied(const char *command)
{
    dprintf(2, "\033[0;31m%s: Permission denied.\033[0m\n", command);
    return SHELL_ERROR;
}

int wrong_architecture(const char *command)
{
    dprintf(2, "\033[0;31m%s: Exec format error. "
    "Wrong Architecture.\n", command);
    return SHELL_ERROR;
}

int error_in_command(const char *command, const char *pathcommand)
{
    if (command == NULL)
        return SHELL_ERROR;
    if (pathcommand == NULL)
        return command_not_found(command);
    if (access(pathcommand, F_OK) != 0 ||
    (access(pathcommand, F_OK) == 0 && !is_a_binary(pathcommand)
    && is_in_current_dir(pathcommand)))
        return command_not_found(command);
    if (access(pathcommand, X_OK) != 0 && is_a_binary(command))
        return permission_denied(command);
    return SUCCESS;
}
