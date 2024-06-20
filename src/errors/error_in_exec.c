/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** error_in_exec
*/

#include "mysh.h"
#include "macros.h"

bool do_not_have_access(char *command, int *error)
{
    if (access(command, F_OK) == 0) {
        if (access(command, X_OK) != 0) {
            dprintf(2, "\033[0;31m%s: Permission denied.\033[0m\n", command);
            *error = SHELL_ERROR;
            return true;
        }
    }
    if (access(command, F_OK) != 0) {
        *error = NOT_FOUND;
        free(command);
        return true;
    }
    return false;
}

int wrong_arch(const char *exec, int *error)
{
    if (errno == 0)
        return CHILD_LEAVING;
    if (errno == EACCES || errno == EISDIR)
        *error = permission_denied(exec);
    if (errno == ENOEXEC)
        *error = wrong_architecture(exec);
    return CHILD_LEAVING;
}

int handle_errors(int error, char *const *args)
{
    if (error == NOT_FOUND && errno == ENOENT) {
        dprintf(2, "\033[0;31m%s: Command not found.\033[0m\n", args[0]);
        return SHELL_ERROR;
    }
    if (error == 0)
        return SUCCESS;
    else
        return SHELL_ERROR;
}

int wstatus(int status)
{
    if (!WIFSIGNALED(status))
        return SUCCESS;
    if (WTERMSIG(status) == SIGSEGV) {
        if (WCOREDUMP(status))
            dprintf(2, "\033[0;31mSegmentation fault (core dumped)\033[0m\n");
        else
            mini_printf("%s\n", strsignal(11));
        status = (status < 128 ? 128 + status : status);
        return status;
    } else if (WTERMSIG(status) == SIGFPE) {
        dprintf(2, "\033[0;31mFloating exception (core dumped)\033[0m\n");
        status = (status < 128 ? 128 + status : status);
        return status;
    }
    return SHELL_ERROR;
}
