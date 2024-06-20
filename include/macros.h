/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** macros
*/

#ifndef MACROS_MYSH
    #define MACROS_MYSH
    #include <fcntl.h>

// int MACROS

//-- return_values --//

    #define ERROR 84
    #define SUCCESS 0
    #define FAILURE -1
    #define SHELL_ERROR 1

//-- !return_values! --//

    #define COMMON_COMMAND 257

    #define ERROR_EXEC 256
    #define SEGV 512

    #define NOT_FOUND -1

//-- size --//

    #define RIGHT_SIZE SUCCESS
    #define WRONG_SIZE SHELL_ERROR
    #define NO_SIZE 0

//-- !size! --//

    #define NO_ERROR NO_SIZE
    #define NOT_A_COMMAND NO_ERROR

    #define START 0

//-- file_descriptors --//

    #define READ 0
    #define WRITE 1

//-- !file_descriptors! --//

    #define SIMILAR SUCCESS

    #define CHILD_LEAVING 84
    #define LEAVING 2312

    #define END_OF_TRANSMISSION 4

    #define S_IRWUSR S_IRUSR + S_IWUSR
    #define BASIC_RIGHTS S_IRWUSR + S_IRGRP + S_IROTH

// str MACROS

    #define PIPE_STR "|"

// char MACROS

    #define PIPE_CHAR '|'
    #define END_OF_STR '\0'
    #define BACKSPACE '\n'

// built-in

    #define CD_CMD "cd"
    #define ENV_CMD "env"
    #define EXIT_CMD "exit"
    #define ECHO_CMD "echo"
    #define SETENV_CMD "setenv"
    #define UNSETENV_CMD "unsetenv"

// handle string

    #define PROMPT -2

#endif /* !MACROS_MYSH */
