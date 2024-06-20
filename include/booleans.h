/*
** EPITECH PROJECT, 2024
** booleans.h
** File description:
** boolean functions
*/

#ifndef BOOLEANS
    #define BOOLEANS
    #include <stdbool.h>

bool is_alpha(char c);
bool is_digit(char c);
bool is_alphanum(char c);
bool is_maj_alpha(char c);
bool is_min_alpha(char c);
bool is_only_alphanum(char *str);

#endif /* BOOLEANS */
