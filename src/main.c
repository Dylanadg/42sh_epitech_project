/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main
*/

#include "mysh.h"
#include "macros.h"

int main(int ac, const char **av, const char **env)
{
    (void)av;
    if (ac != 1)
        return ERROR;
    return my_shell(env);
}
