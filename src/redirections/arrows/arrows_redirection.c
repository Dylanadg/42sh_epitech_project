/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** arrow_redirection
*/

#include "mysh.h"
#include "macros.h"
#include "redirection.h"

int arrows_redirection(const char *const *commands, const char **paths,
    list_t **env, size_t j)
{
    for (int i = RIGHT_ARROW; i != NB_SEP; i++) {
        if (my_strcmp(redirections[i].sep, commands[j + 1]) == 0
        && redirections[i].function != NULL)
            return redirections[i].function(commands[j],
            commands[j + 2], env, paths);
    }
    return SUCCESS;
}
