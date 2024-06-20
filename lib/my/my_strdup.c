/*
** EPITECH PROJECT, 2023
** my_strdup.c
** File description:
** my_strdup.c
*/
#include "mysh.h"

char *my_strdup(char const *src)
{
    int size = my_strlen(src) + 1;
    char *dest = NULL;
    int i = 0;

    if (src == NULL)
        return NULL;
    dest = malloc(sizeof(char) * size);
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
