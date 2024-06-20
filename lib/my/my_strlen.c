/*
** EPITECH PROJECT, 2023
** my_strlen.c
** File description:
** my_strlen
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int rep = 0;

    if (str == NULL)
        return 0;
    while (str[rep] != '\0')
        rep ++;
    return rep;
}
