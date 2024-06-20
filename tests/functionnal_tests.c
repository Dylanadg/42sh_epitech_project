/*
** EPITECH PROJECT, 2024
** functionnal_tests
** File description:
** functionnal_tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh.h"


Test(cd, error_NULL) {
    int result = execute_cd(NULL, NULL);

    cr_assert_eq(result, 1, "Executed cd without error but shouldn't.");
}

Test(cd, go_back) {
    char *path_before = getcwd(NULL, 0);
    char **array = malloc(sizeof(char *) * 3);
    char *path_after = NULL;
    int result = 0;

    array[0] = "cd";
    array[1] = "..";
    array[2] = NULL;
    result = execute_cd(array, NULL);
    path_after = getcwd(NULL, 0);
    cr_assert_eq(result, 0, "An error occured.");
    cr_assert_str_neq(path_before, path_after, "Directory hasn't changed");
}

Test(cd, go_home_01_1) {
    char **array = malloc(sizeof(char *) * 3);
    list_t *env = malloc(sizeof(list_t));
    char *path = NULL;
    int result = 0;

    array[0] = "cd";
    array[1] = "~";
    array[2] = NULL;
    env->var = "HOME";
    env->value = "/home";
    env->next = NULL;
    result = execute_cd(array, env);
    path = getcwd(NULL, 0);
    cr_assert_eq(result, 0, "An error occured.");
    cr_assert_str_eq(path, "/home", "Didn't come back home, path is %s", path);
}

Test(cd, go_home_01_2) {
    char **array = malloc(sizeof(char *) * 3);
    list_t *env = malloc(sizeof(list_t));
    char *initial_path = getcwd(NULL, 0);
    char *path = NULL;
    int result = 0;

    array[0] = "cd";
    array[1] = "~";
    array[2] = NULL;
    env->var = "HOME";
    env->value = NULL;
    env->next = NULL;
    result = execute_cd(array, env);
    path = getcwd(NULL, 0);
    cr_assert_eq(result, 1, "An error occured.");
    cr_assert_str_eq(path, initial_path, "Came back home, but there is no path");
}

Test(cd, go_home_01_3) {
    char **array = malloc(sizeof(char *) * 3);
    char *path = NULL;
    int result = 0;

    array[0] = "cd";
    array[1] = "~";
    array[2] = NULL;
    result = execute_cd(array, NULL);
    path = getcwd(NULL, 0);
    cr_assert_eq(result, 1, "Found its way to home without HOME var in env.");
    cr_assert_str_neq(path, "/home", "Came back home, path is /home");
}

Test(cd, go_home_02_1) {
    char **array = malloc(sizeof(char *) * 2);
    char *path = NULL;
    int result = 0;

    array[0] = "cd";
    array[1] = NULL;
    result = execute_cd(array, NULL);
    path = getcwd(NULL, 0);
    cr_assert_eq(result, 1, "Found its way to home without HOME var in env.");
    cr_assert_str_neq(path, "/home", "Didn't come back home, path is %s", path);
}

Test(cd, go_home_02_2) {
    char **array = malloc(sizeof(char *) * 2);
    list_t *env = malloc(sizeof(list_t));
    char *path = NULL;
    int result = 0;

    array[0] = "cd";
    array[1] = NULL;
    env->var = "HOME";
    env->value = NULL;
    env->next = NULL;
    result = execute_cd(array, env);
    path = getcwd(NULL, 0);
    cr_assert_eq(result, 1, "An error occured.");
    cr_assert_str_neq(path, "/home", "Came back home but path was null");
}

Test(cd, go_home_03) {
    char **array = malloc(sizeof(char *) * 3);
    char *path = NULL;
    int result = 0;

    array[0] = "cd";
    array[1] = "/home";
    array[2] = NULL;
    result = execute_cd(array, NULL);
    path = getcwd(NULL, 0);
    cr_assert_eq(result, 0, "An error occured.");
    cr_assert_str_eq(path, "/home", "Didn't come back home, path is %s", path);
}

Test(cd, go_to_unvalid_dest) {
    char *path_before = getcwd(NULL, 0);
    char **array = malloc(sizeof(char *) * 3);
    char *path_after = NULL;
    int result = 0;

    array[0] = "cd";
    array[1] = "dbuazoadp6e9a";
    array[2] = NULL;
    result = execute_cd(array, NULL);
    path_after = getcwd(NULL, 0);
    cr_assert_eq(result, 1, "An error should have occured.");
    cr_assert_str_eq(path_before, path_after, "Should've stayed but went somewhere.");
}


Test(env, env_with_args) {
    char **array = malloc(sizeof(char *) * 3);
    list_t *env = malloc(sizeof(list_t));
    int result = 0;

    array[0] = "env";
    array[1] = "something";
    array[2] = NULL;
    result = execute_env(env, array);
    cr_assert_eq(result, 1, "An error should have occured: putted an arg");
}

Test(cd, go_in_file) {
    char *path_before = getcwd(NULL, 0);
    char **array = malloc(sizeof(char *) * 3);
    char *path_after = NULL;
    int result = 0;

    array[0] = "cd";
    array[1] = "src/main.c";
    array[2] = NULL;
    result = execute_cd(array, NULL);
    path_after = getcwd(NULL, 0);
    cr_assert_eq(result, 1, "An error should have occured.");
    cr_assert_str_eq(path_before, path_after, "Probably went to a file but this action shouldn't be allowed.");
}

Test(cd, cd_back) {
    char **array = malloc(sizeof(char *) * 3);
    list_t *env = malloc(sizeof(list_t));
    char *path_before = getcwd(NULL, 0);
    char *path_after = NULL;
    int result = 0;

    array[0] = "cd";
    array[1] = "-";
    array[2] = NULL;
    env->var = "OLDPWD";
    env->value = "/etc";
    env->next = NULL;
    result = execute_cd(array, env);
    path_after = getcwd(NULL, 0);
    cr_assert_eq(result, 0, "An error occured.");
    cr_assert_str_neq(path_before, path_after, "Changing directory hasn't worked out.");
}

Test(contain_error, case_01) {
    bool error = contain_error("_hey");

    cr_assert_eq(error, true, "Not considered as an invalid name but starts with non alpha char.");
}

Test(contain_error, case_02) {
    bool error = contain_error("Hey!");

    cr_assert_eq(error, true, "Not considered as an invalid name but has non alphanumeric char.");
}

Test(contain_error, case_03) {
    bool error = contain_error("Hey");

    cr_assert_eq(error, false, "Considered as an invalid name...");
}

Test(execute_env, all_null) {
    int error = execute_env(NULL, NULL);

    cr_assert_eq(error, 0, "len considered as > 1.");
}

Test(execute_env, command_null) {
    list_t *env = malloc(sizeof(list_t));
    int error = 0;

    env->value = "PATH";
    env->var = "/bin";
    env->next = NULL;
    error = execute_env(env, NULL);
    cr_assert_eq(error, 0, "len considered as > 1.");
}

Test(execute_env, env_null) {
    char **command = malloc(sizeof(char *) * 3);
    int error = 0;

    command[0] = "env";
    command[1] = "*";
    command[2] = NULL;
    error = execute_env(NULL, command);
    cr_assert_eq(error, 1, "len considered as <= 1.");
}

Test(execute_unsetenv, unset_all) {
    char **command = malloc(sizeof(char *) * 3);
    list_t *env = malloc(sizeof(list_t));
    list_t *next_node = malloc(sizeof(list_t));
    int error = 0;

    next_node->value = "PATH";
    next_node->var = "/bin";
    next_node->next = NULL;
    env->value = "o_";
    env->var = "_o";
    env->next = next_node;
    command[0] = "PATH";
    command[1] = "o_";
    command[2] = NULL;
    error = execute_unsetenv(&env, command);
    cr_assert_eq(error, 0, "Delete returned an error.");
}

Test(execute_unsetenv, unset_inexistent) {
    char **command = malloc(sizeof(char *) * 3);
    int error = 0;

    command[0] = "PATH";
    command[1] = "o_";
    command[2] = NULL;
    error = execute_unsetenv(NULL, command);
    cr_assert_eq(error, 0, "Delete returned an error.");
}

Test(execute_unsetenv, unset_star) {
    char **command = malloc(sizeof(char *) * 2);
    int error = 0;

    command[0] = "*";
    command[1] = NULL;
    error = execute_unsetenv(NULL, command);
    cr_assert_eq(error, 0, "Detected * as an error.");
}

Test(is_pipe, not_a_pipe) {
    const char *str = "hey!";

    cr_assert_eq(is_pipe(str), false, "Considered 'hey!' as a pipe.");
}

Test(is_pipe, is_pipe) {
    const char *str = "|";

    cr_assert_eq(is_pipe(str), true, "Didn't considered '|' as a pipe.");
}

Test(is_pipe, is_null) {
    const char *str = NULL;

    cr_assert_eq(is_pipe(str), false, "Didn't considered '|' as a pipe.");
}

Test(is_arrow_redirection, is_arrow) {
    const char *str = ">";

    cr_assert_eq(is_arrow_redirection(str), true, "Didn't considered '>' as an arrow.");
}

Test(is_arrow_redirection, is_not_only_arrow) {
    const char *str = "<3";

    cr_assert_eq(is_arrow_redirection(str), false, "Considered '<3' as an arrow.");
}

Test(is_arrow_redirection, is_not_arrow) {
    const char *str = "3";

    cr_assert_eq(is_arrow_redirection(str), false, "Considered '3' as an arrow.");
}

Test(is_redirection, is_null) {
    const char *str = NULL;

    cr_assert_eq(is_redirection(str), false, "Considered NULL as a redirection.");
}

Test(is_redirection, is) {
    const char *str = ">>";

    cr_assert_eq(is_redirection(str), true, "Didn't considered '>>' as a redirection.");
}

Test(is_redirection, is_not) {
    const char *str = "";

    cr_assert_eq(is_redirection(str), false, "Considered '' as a redirection.");
}

Test(is_not_ambiguous, is_two_arrows) {
    char **array = malloc(sizeof(char *) * 5);

    array[0] = "hey";
    array[1] = ">";
    array[2] = "it's a success";
    array[3] = "<";
    array[4] = NULL;
    cr_assert_eq(is_not_ambiguous((const char **)array), false, "Didn't detected a succession of two arrows.");
}

Test(is_not_ambiguous, is_not) {
    char **array = malloc(sizeof(char *) * 5);

    array[0] = "hey";
    array[1] = ">";
    array[2] = "it's a success";
    array[3] = ";";
    array[4] = NULL;
    cr_assert_eq(is_not_ambiguous((const char **)array), true, "Succession of arrow and semicolon considered as ambiguous.");
}

Test(is_not_ambiguous, is_arrow_and_pipe) {
    char **array = malloc(sizeof(char *) * 5);

    array[0] = "hey";
    array[1] = ">";
    array[2] = "it's a success";
    array[3] = "|";
    array[4] = NULL;
    cr_assert_eq(is_not_ambiguous((const char **)array), false, "Didn't detected a succession of arrow and pipe.");
}

Test(delete_backspace, with_back) {
    char *command = malloc(sizeof(char) * 5);

    command[0] = 'h';
    command[1] = 'e';
    command[2] = 'y';
    command[3] = '\n';
    command[4] = '\0';
    delete_backspace(&command);
    cr_assert_str_eq(command, "hey", "Didn't deleted the backspace.");
}

Test(delete_backspace, without_back) {
    char *command = malloc(sizeof(char) * 5);
    bool error = false;

    command[0] = 'h';
    command[1] = 'e';
    command[2] = 'y';
    command[3] = '!';
    command[4] = '\0';
    error = delete_backspace(&command);
    cr_assert_eq(error, false, "Wrong return value.");
    cr_assert_str_eq(command, "hey!", "Didn't considered as an error the fact there is no '\\n': '%s'.", command);
}

Test(delete_backspace, with_null) {
    char *command = NULL;
    bool error = delete_backspace(&command);

    cr_assert_eq(command, NULL, "Changed the NULL: %s.", command);
    cr_assert_eq(error, false, "Changed the NULL: %s.", command);
}

Test(divide_line, null_line)
{
    char **array = divide_line("hey=bonjour", '=');

    cr_assert_str_eq(array[0], "hey", "Didn't crop correctly: '%s'.", array[0]);
    cr_assert_str_eq(array[1], "bonjour", "Didn't crop correctly: '%s'.", array[1]);
}

Test(fill_list, null_line)
{
    char *line_array = "hey";
    list_t *list = NULL;

    fill_list(line_array, &list);
    cr_assert_neq(list, NULL, "Did not fill correctly the list.");
    cr_assert_eq(list->next, NULL, "Did not fill correctly the list->next.");
    cr_assert_str_eq(list->value, "", "Did not fill correctly the list->value: '%s'.", list->value);
    cr_assert_str_eq(list->var, "hey", "Did not fill correctly the list->var.");
}


Test(get_paths, no_paths)
{
    char **paths = get_paths(NULL);

    cr_assert_eq(paths, NULL, "Filled paths without even finding one.");
}

Test(get_paths, paths)
{
    list_t *list = malloc(sizeof(list_t));
    char **paths = NULL;

    list->var = "PATH";
    list->value = "/bin/";
    list->next = NULL;
    paths = get_paths(list);
    cr_assert_neq(paths, NULL, "Didn't recognized PATH var in the list: %s", paths[0]);
    cr_assert_str_eq(paths[0], "/bin/", "Didn't cropped PATH value correctly: %s", paths[0]);
}


Test(has_redirection, null_redirection)
{
    char *string = NULL;

    cr_assert_eq(has_redirection(string), false, "Considered NULL as redirection.");
}

Test(has_redirection, no_redirection)
{
    char *string = "hey hey";

    cr_assert_eq(has_redirection(string), false, "Considered a redirection exists in 'hey hey'.");
}

Test(has_redirection, has_redirection)
{
    char *string = "hey > hey";

    cr_assert_eq(has_redirection(string), true, "Considered no redirection exists in 'hey > hey'.");
}

Test(is_a_binary, is_not)
{
    char *string = "hey";

    cr_assert_eq(is_a_binary(string), false, "Considered 'hey' as a binary.");
}

Test(is_a_binary, is)
{
    char *string = "./mysh";

    cr_assert_eq(is_a_binary(string), true, "Didn't considered './mysh' as a binary.");
}

Test(prev_is_command, is_not)
{
    char *string = "> hey";

    cr_assert_eq(prev_is_command(0, string), false, "Found a command before first letter. How curious!");
}

Test(prev_is_command, is)
{
    char *string = "hey > hey";

    cr_assert_eq(prev_is_command(3, string), true, "Didn't find a command before >!");
}

Test(is_in_current_dir, null_command)
{
    char *string = NULL;

    cr_assert_eq(is_in_current_dir(string), false, "null in current directory ??");
}

Test(is_in_current_dir, current_dir)
{
    char *string = "src";

    cr_assert_eq(is_in_current_dir(string), true, "src isn't in current directory ??");
}

Test(is_in_current_dir, not_current_dir)
{
    char *string = "src/main.c";

    cr_assert_eq(is_in_current_dir(string), false, "src/main.c is in current directory ??");
}


Test(divide_line, divide_a_line)
{
    char *string = "hey !";

    cr_assert_neq(divide_line(string, '!'), NULL, "'hey !' returned null");
}

Test(get_path_command, null_command_and_paths)
{
    cr_assert_eq(get_path_command(NULL, NULL), NULL, "Found a path in NULL");
}

Test(get_path_command, command_and_paths)
{
    char *path = "/bin";
    char **paths = &path;

    cr_assert_eq(get_path_command("ejkilo", (const char **)paths), NULL, "Found a path for ejkilo");
}
