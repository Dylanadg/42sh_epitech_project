/*
** EPITECH PROJECT, 2023
** my_strcmp.c
** File description:
** my_strcmp
*/
#include "mysh.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    if (s1 == NULL || s2 == NULL)
        return -257;
    while (s1[i] != '\0' && s2[i] != '\0'
    && s1[i] == s2[i])
        i += 1;
    return (s1[i] - s2[i]);
}
