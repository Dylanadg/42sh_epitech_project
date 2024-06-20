/*
** EPITECH PROJECT, 2024
** bs-minishell2
** File description:
** main
*/

#include "mysh.h"
#include "macros.h"

int pipe_redirection(const char *command, list_t **env_list,
    const char **paths, int *fd)
{
    char **instructions = my_str_to_word_array(command, ' ');
    int error = 0;

    close(fd[READ]);
    dup2(fd[WRITE], STDOUT_FILENO);
    if (instructions == NULL)
        exit(SHELL_ERROR);
    if (special_command(instructions, env_list, error) == COMMON_COMMAND)
        error = execute_command(command, paths, env_list, NO_ERROR);
    free_array(instructions);
    close(fd[WRITE]);
    exit(error);
}

int redirect_pipe(const char *command, const char **paths,
    list_t **env, int *fd)
{
    int pid = 0;

    if (pipe(fd) == -1)
        return SHELL_ERROR;
    pid = fork();
    if (pid == 0)
        pipe_redirection(command, env, paths, fd);
    close(fd[WRITE]);
    dup2(fd[READ], 0);
    close(fd[READ]);
    return SUCCESS;
}
