/*
** EPITECH PROJECT, 2024
** handle_string.c
** File description:
** fct to handle string in a command line with return an array
*/

#include "mysh.h"
#include "macros.h"

static int error_message_crop_string(void)
{
    printf("Unmatched \'\"\'.\n");
    return -1;
}

static void count_quote(bool *in_quote, bool *in_dbl_quote, char c,
    int *nb_word)
{
    if (c == '"' && *in_quote == false)
        *in_dbl_quote = !*in_dbl_quote;
    if (c == '\'' && *in_dbl_quote == false)
        *in_quote = !*in_quote;
    if (*in_quote || *in_dbl_quote)
        (*nb_word) += 1;
    return;
}

static int verif_separator(const char *str, int i, char sep)
{
    if (str[i] != sep && str[i] != '\t' && (str[i + 1] == sep ||
    str[i + 1] == '\t' || str[i + 1] == '\0'))
        return 0;
    return 1;
}

static int count_wrd_pop_string(const char *str, char sep)
{
    int nb_word = 0;
    bool in_quote = false;
    bool in_dbl_quote = false;

    if (str == NULL)
        return FAILURE;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '"' || str[i] == '\'')
            count_quote(&in_quote, &in_dbl_quote, str[i], &nb_word);
        if ((str[i] != '"' && str[i] != '\'') && (in_quote == false &&
        in_dbl_quote == false) && verif_separator(str, i, sep) == 0)
            nb_word += 1;
    }
    if (in_quote == true || in_dbl_quote == true)
        return error_message_crop_string();
    return nb_word;
}

static void nb_cols_arr_crop_str(const char *str, size_t *i, int *j, char sep)
{
    bool in_quotes = false;

    while (str[*i] == sep || str[*i] == '\t')
        (*i) += 1;
    while ((str[*i] != sep && str[*i] != '\t' && str[*i] != '\0') ||
    (in_quotes == true)) {
        if (str[*i] == '"' || str[*i] == '\'') {
            in_quotes = !in_quotes;
        }
        if (in_quotes || (str[*i] != sep && str[*i] != '\t')) {
            (*j) += 1;
        }
        (*i) += 1;
    }
    return;
}

static char *words_create_corp_str(const char *str, char *new_string,
    size_t *i, int j)
{
    int k = 0;
    bool in_quotes = false;

    for (k = 0; k != j; k++) {
        if (str[*i] == '"' || str[*i] == '\'') {
            in_quotes = !in_quotes;
        }
        if ((in_quotes && (str[*i] != '"' || str[*i] == '\'')) ||
        (str[*i] != ' ' && str[*i] != '\t'))
            new_string[k] = str[*i];
        else
            k -= 1;
        (*i) += 1;
    }
    new_string[k] = '\0';
    return new_string;
}

static char **create_array_crop_str(const char *str, char sep, int nb_mot)
{
    char **array = malloc((nb_mot + 1) * sizeof(char *));
    char *new_str = NULL;
    int index = 0;
    int y = 0;
    size_t len = (size_t)my_strlen(str);

    for (size_t i = 0; i <= len; i++) {
        nb_cols_arr_crop_str(str, &i, &y, sep);
        new_str = malloc(sizeof(char) * (y + 1));
        i -= y;
        new_str = words_create_corp_str(str, new_str, &i, y);
        array[index] = new_str;
        index += 1;
        y = 0;
    }
    array[nb_mot] = NULL;
    return array;
}

static void clear_quote(char **beg)
{
    char *str = *beg;
    size_t j = 0;

    if (str == NULL)
        return;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] != '"' && str[i] != '\'') {
            str[j] = str[i];
            j += 1;
        }
    }
    str[j] = '\0';
}

char **crop_strings(const char *command, char sep)
{
    int nb_word = count_wrd_pop_string(command, sep);
    char **arr;
    int i = 0;

    if (nb_word == -1)
        return NULL;
    arr = create_array_crop_str(command, sep, nb_word);
    if (arr == NULL || *arr == NULL)
        return NULL;
    while (arr[i] != NULL) {
        if (arr[i][0] == '"' || arr[i][0] == '\'')
            clear_quote(&arr[i]);
        i += 1;
    }
    return arr;
}
