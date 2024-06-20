/*
** EPITECH PROJECT, 2024
** list_to_array.c
** File description:
** env to array
*/

#include "mysh.h"

int size_first_word(const char *word, int sep)
{
    int size = 0;

    if (word == NULL)
        return size;
    while (word[size] != sep && word[size] != '\0')
        size += 1;
    return size;
}

char **divide_line(const char *line, char sep)
{
    char **arr_line = malloc(sizeof(char *) * 3);
    int size = my_strlen(line);
    int size_value = size_first_word(line, sep);
    int j = 0;
    int a = 0;

    arr_line[0] = malloc(sizeof(char) * (size_value + 1));
    arr_line[1] = malloc(sizeof(char) * (size - size_value + 1));
    for (int i = 0; line[i] != '\0'; i++) {
        arr_line[j][a] = line[i];
        if (j == 0 && line[i] == sep) {
            arr_line[j][a] = '\0';
            j++;
            a = -1;
        }
        a += 1;
    }
    arr_line[j][a] = '\0';
    arr_line[2] = NULL;
    return arr_line;
}

static size_t get_size_list(list_t *list)
{
    size_t size = 0;

    while (list != NULL) {
        size += 1;
        list = list->next;
    }
    return size;
}

void fill_list(const char *line_of_array, list_t **initial_list)
{
    char **line = divide_line(line_of_array, '=');
    list_t *list = create_node(line[0], line[1]);
    list_t *tmp = *initial_list;

    free_array(line);
    if (tmp == NULL) {
        *initial_list = list;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = list;
    return;
}

list_t *array_to_list(const char *const *array)
{
    list_t *list = NULL;

    if (array == NULL)
        return NULL;
    for (int i = 0; array[i] != NULL; i++)
        fill_list(array[i], &list);
    return list;
}

char **list_to_array(list_t *list)
{
    size_t size = get_size_list(list);
    char **array = NULL;

    array = malloc(sizeof(char *) * (size + 1));
    for (size_t i = 0; i < size; i++) {
        array[i] = my_strdup(list->var);
        my_strcat_mod(&array[i], "=");
        my_strcat_mod(&array[i], list->value);
        list = list->next;
    }
    array[size] = NULL;
    return array;
}
