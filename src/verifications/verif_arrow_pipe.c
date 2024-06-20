/*
** EPITECH PROJECT, 2024
** B-PSU-200-PAR-2-1-42sh-leonart.heurteux
** File description:
** verif_arrow_pipe
*/

#include "struct.h"
#include "mysh.h"
#include "macros.h"

int verif_pipe_arrow(const char *const *commands,
    const char **paths, list_t **env, global_t *all)
{
    if (is_pipe(commands[all->j + 1]))
        redirect_pipe(commands[all->j], paths, env, all->fd);
    if (is_arrow_redirection(commands[all->j + 1]))
        arrows_redirection(commands, paths, env, all->j);
    all->j += 2;
    return SUCCESS;
}
