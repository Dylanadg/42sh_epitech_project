/*
** EPITECH PROJECT, 2023
** unitests.c
** File description:
** unitests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh.h"

Test(size_first_word, valid_word)
{
    char *string = "hey!=Gabin";
    size_t size_var = size_first_word(string, '=');

    cr_assert_eq(size_var, 4, "Size invalid: %i", size_var);
}

Test(size_first_word, null_word)
{
    char *string = "hey!=Gabin";
    size_t size_var = size_first_word(NULL, '=');

    cr_assert_eq(size_var, 0, "Size of null invalid: %i", size_var);
}

Test(size_first_word, size_null)
{
    char *string = NULL;

    cr_assert_eq(size_first_word(string, '\0'), 0, "null size != 0");
}

Test(size_first_word, size_word_not_null)
{
    char *string = "hey !";

    cr_assert_eq(size_first_word(string, '!'), 4, "'hey ' size != 4");
}

Test(is_char_redir, right_redirection)
{
    char c = '>';

    cr_assert_eq(is_char_redir(c), true, "Didn't considered > as redirection.");
}

Test(is_char_redir, left_redirection)
{
    char c = '<';

    cr_assert_eq(is_char_redir(c), true, "Didn't considered < as redirection.");
}

Test(is_char_redir, semicolon_redirection)
{
    char c = ';';

    cr_assert_eq(is_char_redir(c), true, "Didn't considered ; as redirection.");
}

Test(is_char_redir, pipe_redirection)
{
    char c = '|';

    cr_assert_eq(is_char_redir(c), true, "Didn't considered | as redirection.");
}

Test(is_char_redir, not_char_redir)
{
    char c = 'o';

    cr_assert_eq(is_char_redir(c), false, "Considered o as redirection.");
}
