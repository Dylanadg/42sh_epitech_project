/*
** EPITECH PROJECT, 2024
** echo.c
** File description:
** echo
*/

#include "macros.h"
#include "mysh.h"

static bool is_env_var(const char *var, list_t **env)
{
    list_t *cpy = *env;

    if (var == NULL)
        return false;
    while (cpy != NULL) {
        if (strcmp(cpy->var, var) == SIMILAR)
            return true;
        cpy = cpy->next;
    }
    return false;
}

static char *delete_dollar(const char *str)
{
    char *new_str = NULL;
    size_t len = 0;

    if (str == NULL)
        return NULL;
    if (str[0] != '$')
        return NULL;
    len = strlen(str);
    new_str = malloc(sizeof(char) * len);
    for (size_t i = 0; str[i] != '\0'; ++i) {
        new_str[i] = str[i + 1];
    }
    return new_str;
}

static char *get_value_of_env_var(const char *var, list_t **env)
{
    list_t *cpy = *env;

    if (var == NULL)
        return false;
    while (cpy != NULL) {
        if (strcmp(cpy->var, var) == SIMILAR)
            return cpy->value;
        cpy = cpy->next;
    }
    return NULL;
}

int handle_echo(const char *const *command, int error, list_t **env)
{
    char *var = NULL;

    if (command[1] == NULL)
        return COMMON_COMMAND;
    if (my_strcmp(command[1], "$?") == SIMILAR) {
        dprintf(1, "%i\n", error);
        return SUCCESS;
    }
    var = delete_dollar(command[1]);
    if (command[1][0] == '$' && is_env_var(var, env)) {
        printf("%s\n", get_value_of_env_var(var, env));
        free(var);
        return SUCCESS;
    }
    free(var);
    return COMMON_COMMAND;
}
