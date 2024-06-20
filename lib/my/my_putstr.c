/*
** EPITECH PROJECT, 2024
** my_putstr.c
** File description:
** my_putstr
*/

#include "mysh.h"

void my_putstr(char *str)
{
    if (str == NULL)
        return;
    write(1, str, my_strlen(str));
}
