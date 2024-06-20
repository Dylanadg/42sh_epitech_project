/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** get_paths
*/

#include "mysh.h"

char **get_paths(list_t *env)
{
    char **all_paths = NULL;
    char *pathline = NULL;
    list_t *temp = env;

    for (int i = 0; temp != NULL; i++) {
        if (is_path((const char *)temp->var)) {
            pathline = my_strdup(temp->value);
            break;
        }
        temp = temp->next;
    }
    if (pathline == NULL)
        return NULL;
    all_paths = my_str_to_word_array(pathline, ':');
    free(pathline);
    return all_paths;
}

char *get_path_command(const char *command, const char **paths)
{
    char *path = NULL;

    if (paths == NULL)
        return NULL;
    if (access(command, F_OK) == 0)
        return my_strdup(command);
    for (int i = 0; paths[i] != NULL; i++) {
        my_strcat_mod(&path, paths[i]);
        my_strcat_mod(&path, "/");
        my_strcat_mod(&path, command);
        if (access(path, F_OK) == 0)
            return path;
        free(path);
        path = NULL;
    }
    return NULL;
}
