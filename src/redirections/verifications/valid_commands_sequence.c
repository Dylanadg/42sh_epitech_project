/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** succession_of_commands
*/

#include "mysh.h"
#include <unistd.h>

bool ambiguous_command(void)
{
    write(2, "Ambiguous output redirect.\n", 27);
    return false;
}

bool missing_name_for_redirect(void)
{
    write(2, "Missing name for redirect.\n", 27);
    return false;
}

bool invalid_null_command(void)
{
    write(2, "Invalid null command.\n", 22);
    return false;
}

bool is_not_ambiguous(const char **commands)
{
    const char *last_sep = NULL;

    for (int i = 0; commands[i] != NULL; i++) {
        if (is_arrow_redirection(last_sep) &&
        (is_arrow_redirection(commands[i]) || is_pipe(commands[i])))
            return ambiguous_command();
        if (is_redirection((const char *)commands[i]))
            last_sep = commands[i];
        if (is_pipe(commands[i]) && is_redirection(commands[i + 1]))
            return invalid_null_command();
    }
    return true;
}

bool is_in_right_order(const char **commands)
{
    size_t last_arg = my_arraylen(commands) - 1;

    if (is_arrow_redirection(commands[0]) &&
    (is_redirection(commands[1]) || commands[1] == NULL))
        return missing_name_for_redirect();
    if (commands == NULL || (is_redirection(commands[0]) &&
        !is_final_command(commands[0])))
        return invalid_null_command();
    for (int i = 1; commands[i] != NULL; i++) {
        if (is_redirection(commands[i]) && ((is_redirection(commands[i - 1])
        && !is_semicolon(commands[i - 1])) || (is_redirection(commands[i + 1])
        && !is_semicolon(commands[i + 1]))))
            return invalid_null_command();
    }
    if (is_arrow_redirection(commands[last_arg]))
        return missing_name_for_redirect();
    if (is_pipe(commands[last_arg]))
        return invalid_null_command();
    return is_not_ambiguous(commands);
}
