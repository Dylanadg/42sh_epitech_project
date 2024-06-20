/*
** EPITECH PROJECT, 2024
** library.h
** File description:
** library
*/

#ifndef LIBRARY
    #define LIBRARY
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include "struct.h"

// lib //

int my_strncmp(char const *s1, char const *s2, int n);
char *my_strcat_nofree(char *dest, char const *src);
bool my_strcat_mod(char **dest, char const *src);
char **my_str_to_word_array(const char *, char);
int my_strcmp(char const *s1, char const *s2);
char *my_strcat(char *dest, char const *src);
int delete_in_list(list_t **list, char *var);
size_t my_arraylen(const char *const *array);
char *array_to_str(const char **array);
void my_put_array(char const **array);
int mini_printf(const char *, ...);
char *my_strdup(char const *src);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void free_array(char **array);
void free_list(list_t *list);
void my_put_float(float nb);
void my_putstr(char *str);
void my_put_nbr(int nb);
void my_putchar(char c);
int my_abs(int nb);

#endif /* !LIBRARY */
