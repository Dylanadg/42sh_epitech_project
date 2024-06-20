/*
** EPITECH PROJECT, 2023
** my_str_to_word_array.c
** File description:
** str to array
*/

#include "mysh.h"

int count_words(const char *str, char sep)
{
    int nb_words = 0;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != sep && str[i] != '\t' &&
        (str[i + 1] == sep || str[i + 1] == '\t' || str[i + 1] == '\0'))
            nb_words++;
    }
    return nb_words;
}

void nb_cols_arr(const char *str, int *i, int *j, char sep)
{
    while (str[*i] == sep || str[*i] == '\t')
        *i += 1;
    while (str[*i] != sep && str[*i] != '\t' && str[*i] != '\0') {
        *j += 1;
        *i += 1;
    }
    return;
}

char *words_create(const char *str, char *new_string, int *i, int j)
{
    for (int k = 0; k != j; k++) {
        new_string[k] = str[*i];
        *i += 1;
    }
    if (str[*i] == '\0')
        *i -= 1;
    new_string[j] = '\0';
    return new_string;
}

char **my_str_to_word_array(const char *str, char sep)
{
    int nb_words = count_words(str, sep);
    char **array = malloc(sizeof(char *) * (nb_words + 1));
    char *new_string = NULL;
    int j = 0;
    int index = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        nb_cols_arr(str, &i, &j, sep);
        i = i - j;
        new_string = malloc(sizeof(char) * (j + 1));
        new_string = words_create(str, new_string, &i, j);
        array[index] = new_string;
        index++;
        j = 0;
    }
    array[nb_words] = NULL;
    return array;
}
