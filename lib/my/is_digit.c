/*
** EPITECH PROJECT, 2024
** is_digit.c
** File description:
** verify if a char is a digit
*/

#include "booleans.h"

bool is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}
