/*
** EPITECH PROJECT, 2024
** cd.c
** File description:
** cd command
*/

#include "mysh.h"
#include "macros.h"

int handle_cd_errors(int error, char *destination)
{
    if (error != NOT_FOUND)
        return SUCCESS;
    if (errno == ENOENT && destination != NULL && my_strcmp(destination, "~")
    != 0 && my_strcmp(destination, "-") != 0) {
        write(2, destination, my_strlen(destination));
        write(2, ": No such file or directory.\n", 29);
    }
    if (errno == ENOTDIR) {
        write(2, destination, my_strlen(destination));
        write(2, ": Not a directory.\n", 19);
    }
    if (errno == EACCES) {
        write(2, destination, my_strlen(destination));
        write(2, ": Permission denied.\n", 21);
    }
    return SHELL_ERROR;
}

static char *change_oldpwd(list_t *env)
{
    char *dest = NULL;
    char *current_pwd = getcwd(NULL, 0);

    while (env != NULL) {
        if (my_strcmp(env->var, "OLDPWD") == 0) {
            dest = my_strdup(env->value);
            env->value = my_strdup(current_pwd);
            break;
        }
        if (my_strcmp(env->var, "OLDPWD") != 0 && env->next == NULL)
            execute_setenv(&env, "OLDPWD", NULL);
        env = env->next;
    }
    free(current_pwd);
    return dest;
}

int redirect_to_previous_dest(list_t *env)
{
    char *dest = change_oldpwd(env);
    int error = 0;

    if (dest == NULL) {
        write(2, ": No such file or directory.\n", 29);
        return NOT_FOUND;
    }
    error = chdir(dest);
    free(dest);
    return error;
}

static bool used_correctly(char **command, int size)
{
    if (command == NULL)
        return false;
    if (size > 2) {
        write(2, "cd: Too many arguments.\n", 24);
        return false;
    }
    if (size < 1)
        return false;
    return true;
}

static bool home_exists(list_t *env)
{
    list_t *tmp = env;

    while (tmp != NULL) {
        if (my_strcmp(tmp->var, "HOME") == 0)
            return true;
        tmp = tmp->next;
    }
    return false;
}

static char *get_home(list_t *env)
{
    list_t *tmp = env;

    while (tmp != NULL) {
        if (my_strcmp(tmp->var, "HOME") == 0)
            return tmp->value;
        tmp = tmp->next;
    }
    return NULL;
}

static int home_inexistent(void)
{
    write(2, "cd: No home directory.\n", 23);
    return SHELL_ERROR;
}

int execute_cd(char **command, list_t *env)
{
    int size = my_arraylen((const char **)command);
    char *destination = NULL;
    int error = 0;

    if (!used_correctly(command, size))
        return SHELL_ERROR;
    if (size == 2)
        destination = command[1];
    if (destination == NULL || my_strcmp(destination, "~") == 0) {
        free(change_oldpwd(env));
        return (home_exists(env) ?
        my_abs(chdir(get_home(env))) : home_inexistent());
    } else if (my_strcmp(destination, "-") == 0) {
        error = redirect_to_previous_dest(env);
    } else {
        free(change_oldpwd(env));
        error = chdir(destination);
    }
    return handle_cd_errors(error, destination);
}
