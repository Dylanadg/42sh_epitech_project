/*
** EPITECH PROJECT, 2024
** is_alphanum.c
** File description:
** verify if a char is an alphanumeric
*/

#include "booleans.h"

bool is_alphanum(char c)
{
    if (is_alpha(c) || is_digit(c))
        return true;
    return false;
}

bool is_only_alphanum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!is_alphanum(str[i]) && str[i] != '_')
            return false;
    return true;
}
