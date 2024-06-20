/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** divide_commands
*/

#include "mysh.h"
#include "macros.h"

bool prev_is_command(size_t ind, const char *str)
{
    for (size_t i = ind; i != 0 && !is_char_redir(str[i]); i--)
        if (str[i] != ' ')
            return true;
    return false;
}

size_t number_of_command(const char *request)
{
    size_t size = 0;

    if (request == NULL)
        return NO_SIZE;
    for (size_t i = 0; request[i] != '\0'; i++) {
        if (!is_char_redir(request[i]) && is_char_redir(request[i + 1])
        && prev_is_command(i, request))
            size += 1;
        if (is_char_redir(request[i]) && !is_char_redir(request[i + 1]))
            size += 1;
        if (!is_char_redir(request[i]) && request[i + 1] == '\0'
        && request[i] != ' ')
            size += 1;
    }
    return size;
}

static size_t count_until_redir(const char *str, size_t ind)
{
    size_t size_command = 0;
    size_t start = ind;

    while (str[ind] != '\0' && !is_char_redir(str[ind])) {
        size_command += 1;
        ind += 1;
    }
    ind -= 1;
    while (ind > start && str[ind] == ' ') {
        size_command -= 1;
        ind -= 1;
    }
    return size_command;
}

static size_t count_redir_chars(const char *str, size_t ind)
{
    int size_command = 0;

    while (str[ind] != '\0' && is_char_redir(str[ind])) {
        size_command += 1;
        ind += 1;
    }
    return size_command;
}

char *crop_command(const char *request, size_t *i, size_t size_word)
{
    char *command = malloc(sizeof(char) * (size_word + 1));
    size_t start = *i;

    if (command == NULL)
        return NULL;
    for (size_t j = 0; request[*i] != '\0' && *i < (start + size_word); j++) {
        command[j] = request[*i];
        *i += 1;
    }
    command[size_word] = '\0';
    *i -= 1;
    return command;
}

char **parse_request(const char *request, size_t nb_words)
{
    char **commands = malloc(sizeof(char *) * (nb_words + 1));
    size_t size_word = 0;
    size_t index = 0;

    if (commands == NULL)
        return NULL;
    for (size_t i = 0; i <= nb_words; i++)
        commands[i] = NULL;
    for (size_t i = 0; request[i] != '\0'; i++) {
        if (request[i] == '\t' || request[i] == ' ')
            continue;
        if (!is_char_redir(request[i]))
            size_word = count_until_redir(request, i);
        else
            size_word = count_redir_chars(request, i);
        commands[index] = crop_command(request, &i, size_word);
        index++;
        size_word = 0;
    }
    return commands;
}

char **divide_commands(const char *request)
{
    size_t nb_commands = 0;
    char *cleared_request = NULL;
    char **commands = NULL;

    if (request == NULL)
        return NULL;
    commands = my_str_to_word_array(request, ' ');
    if (commands == NULL)
        return NULL;
    cleared_request = array_to_str((const char **)commands);
    nb_commands = number_of_command(cleared_request);
    free_array(commands);
    if (cleared_request == NULL)
        return NULL;
    commands = NULL;
    commands = parse_request(cleared_request, nb_commands);
    free(cleared_request);
    return commands;
}
