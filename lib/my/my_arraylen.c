/*
** EPITECH PROJECT, 2023
** my_arraylen.c
** File description:
** my_arraylen
*/
#include <stddef.h>

size_t my_arraylen(const char *const *array)
{
    int nb_lines = 0;

    if (array == NULL)
        return 0;
    while (array[nb_lines] != NULL)
        nb_lines += 1;
    return nb_lines;
}
