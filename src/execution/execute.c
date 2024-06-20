/*
** EPITECH PROJECT, 2024
** execution.c
** File description:
** executing command from those functions
*/

#include "mysh.h"
#include "macros.h"
#include "redirection.h"

int special_command(char **command, list_t **env, int error)
{
    int out = my_getnbr(command[1]);

    if (my_strcmp(command[0], CD_CMD) == SIMILAR)
        return execute_cd(command, *env);
    if (my_strcmp(command[0], EXIT_CMD) == SIMILAR) {
        free_array(command);
        exit(out);
    }
    if (my_strcmp(command[0], ECHO_CMD) == SIMILAR)
        return handle_echo((const char *const *)command, error, env);
    out = handle_env(command, env);
    return out;
}

static int redirection_center(const char *const *commands, const char **paths,
    list_t **env, global_t *all)
{
    if (is_multiple_semicolon(commands[all->j])) {
        all->j += 1;
        return redirection_center(commands, paths, env, all);
    }
    if (all->j != 0 && is_and_redir(commands[all->j - 1])
        && all->error == SUCCESS)
        all->error = execute_command(commands[all->j], paths, env, all->error);
    if (is_final_command(commands[all->j + 1]) ||
        is_and_redir(commands[all->j + 1])) {
        if (all->j == 0 || (all->j > 0 &&
            !is_arrow_redirection(commands[all->j - 1]) &&
            !is_and_redir(commands[all->j - 1])))
            all->error = execute_command(commands[all->j],
                paths, env, NO_ERROR);
        if (commands[all->j + 1] == NULL)
            return CHILD_LEAVING;
    }
    verif_pipe_arrow(commands, paths, env, all);
    return redirection_center(commands, paths, env, all);
}

static int execve_all_commands(char **commands,
    const char **paths, list_t **env, global_t *all)
{
    int pid = 0;
    int stat = 0;

    all->j = 0;
    all->error = 0;
    pid = fork();
    if (pid == -1)
        return SHELL_ERROR;
    if (pid == 0)
        exit(redirection_center((const char *const *)commands,
        paths, env, all));
    waitpid(pid, &stat, 0);
    return wstatus(stat);
}

static int last_command(const char **commands, list_t **env)
{
    size_t last = my_arraylen(commands) - 1;
    char **last_command = my_str_to_word_array(commands[last], ' ');
    int error = 0;

    if (last_command == NULL)
        return COMMON_COMMAND;
    error = special_command(last_command, env, NO_ERROR);
    free_array(last_command);
    return error;
}

static bool is_only_semicolon(const char *request)
{
    for (int i = 0; request[i] != '\0'; i++)
        if (request[i] != '\t' && request[i] != ' ' && request[i] != ';')
            return false;
    return true;
}

static int execute_succession_of_commands(const char *requests,
    const char **paths, list_t **env, global_t *all)
{
    char **commands = NULL;
    int error = 0;
    int exec = 0;

    if (is_only_semicolon(requests))
        return SUCCESS;
    commands = divide_commands(requests);
    if (commands == NULL)
        return SHELL_ERROR;
    if (!is_in_right_order((const char **)commands)) {
        free_array(commands);
        return SHELL_ERROR;
    }
    exec = execve_all_commands(commands, paths, env, all);
    error = last_command((const char **)commands, env);
    free_array(commands);
    return (error == COMMON_COMMAND ? exec : error);
}

static int execve_in_child(const char *command_path,
    char *const *command_array, char *const *env)
{
    int pid = 0;
    int status = 0;

    if (command_path == NULL || command_array == NULL || env == NULL)
        return SHELL_ERROR;
    pid = fork();
    if (pid == -1)
        return SHELL_ERROR;
    if (pid == 0) {
        execve(command_path, command_array, env);
        return wrong_arch(command_array[0], &status);
    }
    waitpid(pid, &status, 0);
    return wstatus(status);
}

int common_command(const char *command, const char **paths,
    list_t **list)
{
    char **env_array = list_to_array(*list);
    char *cmd = my_strdup(command);
    char **command_array = NULL;
    char *command_path = NULL;
    int error = 0;

    cmd = alias(cmd);
    command_array = (cmd == NULL ? NULL : crop_strings(cmd, ' '));
    free(cmd);
    command_path = get_path_command((const char *)command_array[0], paths);
    if (common_command_failed(command_array, command_path, env_array))
        return SHELL_ERROR;
    error = execve_in_child((const char *)command_path,
    (char *const *)command_array, (char *const *)env_array);
    free_array(command_array);
    free_array(env_array);
    free(command_path);
    return error;
}

int execute_command(const char *command, const char **paths,
    list_t **env, int prev_err)
{
    char **array = crop_strings(command, ' ');
    int error = 0;

    if (array == NULL || array[0] == NULL)
        return error;
    error = special_command(array, env, prev_err);
    free_array(array);
    if (error != COMMON_COMMAND)
        return error;
    return common_command(command, paths, env);
}

int execute(const char *command, list_t **env,
    const char **paths, int prev_err)
{
    global_t all = {0};

    if (!has_redirection(command))
        return execute_command(command, (const char **)paths, env, prev_err);
    return execute_succession_of_commands(command, paths, env, &all);
}
