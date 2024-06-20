/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** redirection
*/

#ifndef REDIRECTION
    #define REDIRECTION
    #include <stddef.h>
    #include "mysh.h"

enum {
    SEMICOLON = 0,
    PIPE,
    RIGHT_ARROW,
    AND_AND,
    LEFT_ARROW,
    DOUBLE_RIGHT_ARROW,
    DOUBLE_LEFT_ARROW,
    NB_SEP
};

typedef struct redirect_s {
    char *sep;
    int (*function)(const char *, const char *, list_t **, const char **);
} redirect_t;

static redirect_t const redirections[NB_SEP] = {
    {";", NULL},
    {"|", NULL},
    {"&&", NULL},
    {">", &redirect_to_file},
    {"<", &redirect_to_binary},
    {">>", &add_to_file},
    {"<<", &writing_until_word},
    // {"||", &ou_ou_fonction}
};

#endif /* REDIRECTION */
