/*
** EPITECH PROJECT, 2024
** is_alpha.c
** File description:
** verify if a char is an alpha
*/

#include "booleans.h"

bool is_alpha(char c)
{
    if (is_maj_alpha(c) || is_min_alpha(c))
        return true;
    return false;
}
