/*
** EPITECH PROJECT, 2024
** mysh.h
** File description:
** my_sh
*/

#ifndef SHELL2
    #define SHELL2
    #include <errno.h>
    #include <unistd.h>
    #include <string.h>
    #include <signal.h>
    #include <stdlib.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <time.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <sys/wait.h>
    #include "booleans.h"
    #include "library.h"

//___ src ___//


//___ errors ___//


// error_in_command

int command_not_found(const char *command);
int permission_denied(const char *command);
int wrong_architecture(const char *command);
int error_in_command(const char *command, const char *pathcommand);
int wrong_number_of_arguments(char *function, int len, int required);
bool common_command_failed(char **command_array, char *command_path,
    char **env_array);

// error_in_exec

bool do_not_have_access(char *command, int *error);
int handle_errors(int error, char *const *args);
int wrong_arch(const char *exec, int *error);
int wstatus(int stat);

//___ !errors! ___//


// edit_input.c

int edit_input(char **);

// handle_string.c

char **crop_strings(const char *command, char sep);

// divide_commands.c

char **divide_commands(const char *request);

// alias.c

char *alias(char *command);

// sh.c

bool delete_backspace(char **src);
int my_shell(const char *const *env);

// execute.c

int execute(const char *arg, list_t **env, const char **paths, int error);
int execute_command(const char *command, const char **paths,
    list_t **env, int prev_err);
int special_command(char **command, list_t **env, int error);

// path.c

char **get_paths(list_t *env);
bool is_path(const char *env_line);
char *get_path_command(const char *command, const char **paths);
void try_each_path(char *const *args, const char **paths, char *const *env,
    int *error);

// array_to_env.c

char **list_to_array(list_t *env);
list_t *array_to_list(const char *const *array);
int size_first_word(const char *word, int sep);
char **divide_line(const char *line, char sep);
void fill_list(const char *line, list_t **initial_list);


//___ verif ___//

bool is_in_current_dir(const char *command);
bool both_malloc_failed(char **, char **);
bool is_a_binary(const char *command);
bool is_and_redir(const char *command);
bool and_and_for_divide(char c, char car);

//___ !verif! ___//


//___ commands ___//


// env.c

bool contain_error(char *name);
int handle_env(char **command, list_t **env);
int execute_env(list_t *env, char **command);
int execute_unsetenv(list_t **env, char **var);
int execute_setenv(list_t **env, char *name, char *value);

list_t *create_node(char *var, char *value);

// cd.c

int execute_cd(char **command, list_t *env);

// echo.c

int handle_echo(const char *const *command, int error, list_t **env);

//___ !commands! ___//


//___ redirections ___//


// pipe.c

int redirect_pipe(const char *command, const char **paths,
    list_t **env, int *fd);
int pipe_redirection(const char *command, list_t **env_list,
    const char **paths, int *fd);

//___ !redirections! ___//


//___ verifications ___//

bool is_final_command(const char *command);
bool is_arrow_redirection(const char *command);
bool is_multiple_semicolon(const char *str);
bool has_redirection(const char *string);
bool is_redirection(const char *str);
bool is_right_arrow(const char *str);
bool is_left_arrow(const char *str);
bool is_semicolon(const char *str);
bool is_pipe(const char *str);
bool is_char_redir(char c);

//___ !verifications! ___//


//___ arrows ___//

int redirect_to_binary(const char *command,
    const char *filename, list_t **env, const char **paths);
int redirect_to_file(const char *command,
    const char *filename, list_t **env, const char **paths);
int add_to_file(const char *command,
    const char *filename, list_t **env, const char **paths);
int arrows_redirection(const char *const *commands,
    const char **paths, list_t **env, size_t j);
int writing_until_word(const char *command,
    const char *stop, list_t **env, const char **paths);
int and_and_function(const char *command,
    const char *filename, list_t **env, const char **paths);
int ou_ou_fonction(const char *command,
    const char *filename, list_t **env, const char **paths);

// verif
// int and_and_function(const char *command,
//     const char *filename, list_t **env, const char **paths)
bool prev_is_command(size_t ind, const char *str);
int verif_pipe_arrow(const char *const *commands,
    const char **paths, list_t **env, global_t *all);

//___ !arrows! ___//


// valid_commands_sequence

bool is_in_right_order(const char **commands);
bool is_not_ambiguous(const char **commands);
bool missing_name_for_redirect(void);
bool invalid_null_command(void);
bool ambiguous_command(void);


//___ !src! ___//

#endif /* SHELL2 */
