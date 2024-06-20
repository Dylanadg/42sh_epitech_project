/*
** EPITECH PROJECT, 2024
** alias.c
** File description:
** alias
*/

#include "mysh.h"
#include "macros.h"

static int found_word_condition(char **array, int i, char *word)
{
    int nb_word = my_strlen(word);
    int nb = 0;

    for (int j = 0; j != '\n'; j++) {
        if (nb == nb_word) {
            return 1;
        }
        if (array[i][j] == word[nb]) {
            nb++;
            continue;
        }
        nb = NO_SIZE;
    }
    return SUCCESS;
}

static int found_word(char **array, char *word)
{
    char *word_cpy = my_strcat_nofree(word, " = ");

    for (int i = 0; array[i] != NULL; i++) {
        if (found_word_condition(array, i, word_cpy) == 1) {
            free(word_cpy);
            return i;
        }
    }
    free(word_cpy);
    return NOT_FOUND;
}

static char *filehandler(char *filename)
{
    struct stat st;
    int s = stat(filename, &st);
    int file = 0;
    char *buff;

    file = open(filename, O_CREAT | O_RDONLY);
    if (file == -1)
        return NULL;
    s = st.st_size;
    buff = malloc(sizeof(char) * s + 1);
    if (buff == NULL)
        return NULL;
    read(file, buff, s + 1);
    buff[s] = '\0';
    return buff;
}

char *alias(char *command)
{
    char *file = filehandler(".zshrc");
    char **array = NULL;
    size_t len = 0;
    int nb = 0;

    if (file == NULL)
        return command;
    array = my_str_to_word_array(file, '\n');
    nb = found_word(array, command);
    free(file);
    if (nb != NOT_FOUND) {
        len = my_strlen(command) + 3;
        free(command);
        command = my_strdup(array[nb] + len);
    }
    free_array(array);
    return command;
}
