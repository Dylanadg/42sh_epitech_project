/*
** EPITECH PROJECT, 2024
** is_maj_alpha.c
** File description:
** verify if a character is a maj alpha
*/

#include "booleans.h"

bool is_maj_alpha(char c)
{
    if (c >= 'A' && c <= 'Z')
        return true;
    return false;
}
