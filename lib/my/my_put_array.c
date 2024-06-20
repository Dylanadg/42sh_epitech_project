/*
** EPITECH PROJECT, 2024
** print_array.c
** File description:
** printing the entire array
*/

#include "mysh.h"

void my_put_array(char const **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++)
        write(1, array[i], my_strlen(array[i]));
    return;
}
