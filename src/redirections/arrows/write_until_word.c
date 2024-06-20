/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** write_until_word
*/

#include "macros.h"
#include "mysh.h"

char **remalloc(char **array, char *new_line)
{
    size_t len = my_arraylen((const char *const *)array);
    size_t new_array_len = len + 1;
    char **new_array = NULL;

    new_array = malloc(sizeof(char *) * (new_array_len + 1));
    if (new_array == NULL)
        return NULL;
    if (array != NULL)
    for (int i = 0; array[i] != NULL; i++)
        new_array[i] = my_strdup(array[i]);
    new_array[len] = my_strdup(new_line);
    new_array[new_array_len] = NULL;
    if (array != NULL)
        free_array(array);
    return new_array;
}

char **get_all_inputs(const char *stop)
{
    char **inputs = NULL;
    char *line = NULL;
    size_t size = 0;

    while (getline(&line, &size, stdin) != -1) {
        if (my_strncmp(stop, line, my_strlen(stop)) == 0
        && my_strlen(line) == my_strlen(stop) + 1)
            break;
        inputs = remalloc(inputs, line);
        if (inputs == NULL)
            return NULL;
        write(1, "-> ", 3);
    }
    if (line != NULL)
        free(line);
    return inputs;
}

int redirect_to_input(const char *const *inputs)
{
    int pid = 0;
    int fd[2];

    if (pipe(fd) == -1)
        return SHELL_ERROR;
    pid = fork();
    if (pid == -1)
        return SHELL_ERROR;
    if (pid == 0) {
        close(fd[READ]);
        dup2(fd[WRITE], STDOUT_FILENO);
        for (int i = 0; inputs[i] != NULL; i++)
            write(1, inputs[i], my_strlen(inputs[i]));
        close(fd[WRITE]);
        exit(SUCCESS);
    }
    close(fd[WRITE]);
    dup2(fd[READ], STDIN_FILENO);
    close(fd[READ]);
    return SUCCESS;
}

int writing_until_word(const char *command,
    const char *stop, list_t **env, const char **paths)
{
    char **inputs = NULL;
    int error = 0;

    write(1, "-> ", 3);
    inputs = get_all_inputs(stop);
    if (inputs == NULL)
        return SHELL_ERROR;
    if (redirect_to_input((const char *const *)inputs) == SHELL_ERROR) {
        free_array(inputs);
        return SHELL_ERROR;
    }
    free_array(inputs);
    error = execute_command(command, paths, env, NO_ERROR);
    return (error == EXIT_SUCCESS ? SUCCESS : SHELL_ERROR);
}
