/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** edit.h
*/

#ifndef EDIT_H_
    #define EDIT_H_
    #include <stddef.h>
    #include <termios.h>

    #define DOWN "\033[A"
    #define UP "\033[B"
    #define RIGHT "\033[C"
    #define LEFT "\033[D"
    #define BACK_DEL 127
    #define FORWARD_DEL 126
    #define BEGINNING 0
    #define ESCAPE_CHAR '\033'
    #define LIMIT 4
    #define EXECUTED 1
    #define CONTINUE BEGINNING

    #define MAX_

typedef struct buffer_s {
    char buffer[1024];
    int buff_size;
    int cursor_position;
}buffer_t;

void enable_icanon(struct termios *, struct termios *);
void disable_icanon(struct termios *);

static int arrow_key(buffer_t *, char);
static int forward_delete_key(buffer_t *, char);
static int backward_delete_key(buffer_t *, char);
static int insert(buffer_t *, char);

static int (*user_char[5])(buffer_t *, char) = {arrow_key,
    forward_delete_key, backward_delete_key, insert, NULL};

#endif /* !EDIT_H_ */
