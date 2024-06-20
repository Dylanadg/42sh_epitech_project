/*
** EPITECH PROJECT, 2024
** struct.h
** File description:
** structures
*/

#ifndef STRUCT
    #define STRUCT
    #include <stddef.h>

typedef struct environnement_s {
    char *var;
    char *value;
    struct environnement_s *next;
} list_t;

typedef struct global_s {
    size_t j;
    int error;
    int fd[2];
} global_t;

#endif /* STRUCT */
