/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** redirect_to_file
*/

#include "mysh.h"
#include "macros.h"

static int writing_in_file(const char *command,
    const char *filename, list_t **env, const char **paths)
{
    char **command_line = my_str_to_word_array(command, ' ');
    int error = 0;
    int file = 0;

    if (command_line == NULL)
        return SHELL_ERROR;
    file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, BASIC_RIGHTS);
    if (file == -1)
        return SHELL_ERROR;
    dup2(file, STDOUT_FILENO);
    if (special_command(command_line, env, error) == COMMON_COMMAND)
        error = execute_command(command, paths, env, NO_ERROR);
    free_array(command_line);
    close(file);
    return (error == EXIT_SUCCESS ? SUCCESS : SHELL_ERROR);
}

static int adding_to_file(const char *command,
    const char *filename, list_t **env, const char **paths)
{
    char **command_line = my_str_to_word_array(command, ' ');
    int error = 0;
    int file = 0;

    if (command_line == NULL)
        return SHELL_ERROR;
    file = open(filename, O_CREAT | O_WRONLY | O_APPEND, BASIC_RIGHTS);
    if (file == -1)
        return SHELL_ERROR;
    dup2(file, STDOUT_FILENO);
    if (special_command(command_line, env, error) == COMMON_COMMAND)
        error = execute_command(command, paths, env, NO_ERROR);
    free_array(command_line);
    close(file);
    return (error == EXIT_SUCCESS ? SUCCESS : SHELL_ERROR);
}

int add_to_file(const char *command, const char *filename, list_t **env,
    const char **paths)
{
    pid_t pid = 0;
    int waiting = 0;

    pid = fork();
    if (pid == -1)
        return SHELL_ERROR;
    if (pid == 0)
        exit(adding_to_file(command, filename, env, paths));
    waitpid(pid, &waiting, 0);
    return wstatus(waiting);
}

int redirect_to_file(const char *command, const char *filename, list_t **env,
    const char **paths)
{
    pid_t pid = 0;
    int waiting = 0;

    pid = fork();
    if (pid == -1)
        return SHELL_ERROR;
    if (pid == 0)
        exit(writing_in_file(command, filename, env, paths));
    waitpid(pid, &waiting, 0);
    return wstatus(waiting);
}
