/*
** EPITECH PROJECT, 2024
** sh.c
** File description:
** sh
*/

#include "mysh.h"
#include "macros.h"

bool delete_backspace(char **src)
{
    int size = my_strlen(*src);
    char *str = NULL;

    if (src == NULL || *src == NULL || size <= 0)
        return false;
    str = malloc(sizeof(char) * size);
    for (int i = 0; (*src)[i] != '\n'; i++) {
        if ((*src)[i] == '\0') {
            free(str);
            return false;
        }
        str[i] = (*src)[i];
    }
    str[size - 1] = '\0';
    free(*src);
    *src = str;
    return true;
}

void receive_command(list_t **env, char **paths, int *error, size_t nb)
{
    char *input = NULL;
    int sig = 0;

    if (!isatty(STDIN_FILENO))
        sig = getline(&input, &nb, stdin);
    else
        sig = edit_input(&input);
    if (sig == -1) {
        free(input);
        if (isatty(STDIN_FILENO))
            write(1, "exit\n", 5);
        *error = *error + LEAVING;
        return;
    }
    if (isatty(STDIN_FILENO))
        printf("\n");
    delete_backspace(&input);
    if (input != NULL && my_strcmp(input, "\0"))
        *error = execute(input, env, (const char **)paths, *error);
    free(input);
}

static void print_prompt(int error, char **array_path, ssize_t current_dir)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (error != SUCCESS) {
        printf("\033[0;36m[\033[0;32m%02d-%02d-%d \033[0;36m| %s]"
    "\033[0;31m ➜  \033[0m", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
    (array_path == NULL || array_path[current_dir] == NULL ?
    "/" : array_path[current_dir]));
        return;
    }
    printf("\033[0;36m[\033[0;32m%02d-%02d-%d \033[0;36m| %s]"
    "\033[0;32m ➜  \033[0m", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
    (array_path == NULL || array_path[current_dir] == NULL ?
    "/" : array_path[current_dir]));
}

static void prompt(int error)
{
    char *current_path = getcwd(NULL, 0);
    char **array_path = NULL;
    size_t current_dir = 0;

    if (current_path != NULL)
        array_path = my_str_to_word_array(current_path, '/');
    current_dir = my_arraylen((const char *const *)array_path);
    current_dir = (current_dir == 0 ? current_dir : current_dir - 1);
    print_prompt(error, array_path, current_dir);
    free_array(array_path);
    free(current_path);
    return;
}

int my_shell(const char *const *env)
{
    list_t *list_env = array_to_list(env);
    char **paths = get_paths(list_env);
    int error = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            prompt(error);
        receive_command(&list_env, paths, &error, 0);
        if (error == CHILD_LEAVING || error >= LEAVING)
            break;
    }
    free_array(paths);
    free_list(list_env);
    printf("\033[0m");
    return (error >= LEAVING ? error - LEAVING : error);
}
