/*
** EPITECH PROJECT, 2024
** env.c
** File description:
** functions about environnements
*/

#include "mysh.h"
#include "macros.h"

int execute_env(list_t *env, char **command)
{
    int len = my_arraylen((const char **)command);
    char **array_env = NULL;

    if (len > 1)
        return SHELL_ERROR;
    array_env = list_to_array(env);
    if (array_env == NULL)
        return SUCCESS;
    for (int i = 0; array_env[i] != NULL; i++)
        mini_printf("%s\n", array_env[i]);
    free_array(array_env);
    return SUCCESS;
}

bool contain_error(char *name)
{
    if (!is_alpha(name[0])) {
        mini_printf("setenv: Variable name must begin with a letter.\n");
        return true;
    } else if (!is_only_alphanum(name)) {
        mini_printf("setenv: Variable name must contain alphanumeric"
        " characters.\n");
        return true;
    }
    return false;
}

static void create_head_to_list(list_t **env, char *value, char *name)
{
    *env = malloc(sizeof(list_t));
    (*env)->value = my_strdup(value);
    (*env)->var = my_strdup(name);
    (*env)->next = NULL;
}

int execute_setenv(list_t **env, char *name, char *value)
{
    list_t *tmp = *env;

    if (name == NULL || contain_error(name))
        return SHELL_ERROR;
    if (env == NULL || *env == NULL) {
        create_head_to_list(env, value, name);
        return SUCCESS;
    }
    while (tmp != NULL) {
        if (my_strcmp(name, tmp->var) == 0) {
            tmp->value = my_strdup(value);
            return SUCCESS;
        }
        if (tmp->next == NULL)
            tmp->next = create_node(name, value);
        tmp = tmp->next;
    }
    return SHELL_ERROR;
}

int execute_unsetenv(list_t **env, char **vars)
{
    for (int i = 1; vars[i] != NULL; i++) {
        if (my_strcmp(vars[i], "*") == 0)
            return SUCCESS;
    }
    for (int i = 1; vars[i] != NULL; i++)
        delete_in_list(env, vars[i]);
    return SUCCESS;
}

int handle_env(char **command, list_t **env)
{
    int nb_command = my_arraylen((const char **)command);

    if (my_strcmp(command[0], ENV_CMD) == SIMILAR)
        return execute_env(*env, command);
    if (my_strcmp(command[0], SETENV_CMD) == SIMILAR) {
        if (nb_command == 3 || nb_command == 2)
            return execute_setenv(env, command[1], command[2]);
        if (nb_command == 1)
            return execute_env(*env, NULL);
        return wrong_number_of_arguments(command[0], nb_command, 3);
    }
    if (my_strcmp(command[0], UNSETENV_CMD) == SIMILAR) {
        if (nb_command >= 2)
            return execute_unsetenv(env, command);
        return wrong_number_of_arguments(command[0], nb_command, 2);
    }
    return COMMON_COMMAND;
}
