/*
** EPITECH PROJECT, 2024
** is_min_alpha.c
** File description:
** verify if a character is a min alpha
*/

#include "booleans.h"

bool is_min_alpha(char c)
{
    if (c >= 'a' && c <= 'z')
        return true;
    return false;
}
