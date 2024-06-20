/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** redirect_to_binary
*/

#include "mysh.h"
#include "macros.h"

static int writing_file_in_fd(const char *command,
    const char *filename, list_t **env, const char **paths)
{
    char **command_line = my_str_to_word_array(command, ' ');
    int error = 0;
    int file = 0;

    if (command_line == NULL)
        return SHELL_ERROR;
    file = open(filename, O_RDONLY);
    if (file == -1)
        return SHELL_ERROR;
    dup2(file, STDIN_FILENO);
    if (special_command(command_line, env, error) == COMMON_COMMAND) {
        free_array(command_line);
        error = execute_command(command, paths, env, NO_ERROR);
    }
    free_array(command_line);
    close(file);
    return (error == EXIT_SUCCESS ? SUCCESS : SHELL_ERROR);
}

int redirect_to_binary(const char *command,
    const char *filename, list_t **env, const char **paths)
{
    pid_t pid = 0;
    int waiting = 0;

    pid = fork();
    if (pid == -1)
        return SHELL_ERROR;
    if (pid == 0)
        exit(writing_file_in_fd(command, filename, env, paths));
    waitpid(pid, &waiting, 0);
    return wstatus(waiting);
}
