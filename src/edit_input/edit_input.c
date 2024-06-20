/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** arrow_keys_lr.c
*/
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "macros.h"
#include "edit.h"

static void put_return(int cursor_position, int buff_size)
{
    while (cursor_position < buff_size) {
        printf(RIGHT);
        cursor_position += 1;
    }
    return;
}

static void edit_insert(char buffer[], int cursor_position, int buff_size)
{
    int current_position = cursor_position;

    while (current_position < buff_size) {
        printf("%c", buffer[current_position]);
        current_position += 1;
    }
    while (current_position > cursor_position + 1) {
        printf(LEFT);
        current_position -= 1;
    }
    return;
}

static void edit_suppr(char buffer[], int cursor_position, int buff_size)
{
    int current_position = cursor_position;

    while (current_position < buff_size) {
        printf("%c", buffer[current_position]);
        current_position += 1;
    }
    putchar(' ');
    current_position += 1;
    while (current_position > cursor_position) {
        printf(LEFT);
        current_position -= 1;
    }
    return;
}

static void edit_delete(char buffer[], int cursor_position, int buff_size)
{
    int current_position = cursor_position;

    while (current_position > 0) {
        printf(LEFT);
        current_position -= 1;
    }
    while (current_position < buff_size) {
        printf("%c", buffer[current_position]);
        current_position += 1;
    }
    putchar(' ');
    current_position += 1;
    while (current_position > cursor_position) {
        printf(LEFT);
        current_position -= 1;
    }
    return;
}

static int arrow_key(buffer_t *buff, char c)
{
    if (c != '\033')
        return CONTINUE;
    getchar();
    c = getchar();
    switch (c) {
        case 'C':
            if (buff->cursor_position < buff->buff_size) {
                printf(RIGHT);
                buff->cursor_position += 1;
            }
            break;
        case 'D':
            if (buff->cursor_position > 0) {
                printf(LEFT);
                buff->cursor_position -= 1;
            }
            break;
    }
    return EXECUTED;
}

static int insert(buffer_t *buff, char c)
{
    if (c == '\n' || c == EOF || c == '\t')
        return CONTINUE;
    if (buff->cursor_position == buff->buff_size) {
        buff->buffer[buff->cursor_position] = c;
        putchar(c);
        buff->cursor_position += 1;
        buff->buff_size += 1;
    } else {
        memmove(&buff->buffer[buff->cursor_position + 1],
        &buff->buffer[buff->cursor_position],
        buff->buff_size - buff->cursor_position);
        buff->buffer[buff->cursor_position] = c;
        buff->buff_size += 1;
        edit_insert(buff->buffer, buff->cursor_position, buff->buff_size);
        buff->cursor_position += 1;
    }
    return EXECUTED;
}

static int forward_delete_key(buffer_t *buff, char c)
{
    if (c != FORWARD_DEL)
        return CONTINUE;
    if (buff->cursor_position >= BEGINNING &&
    buff->cursor_position < buff->buff_size) {
        memmove(&buff->buffer[buff->cursor_position],
        &buff->buffer[buff->cursor_position + 1],
        buff->buff_size - buff->cursor_position);
        buff->buff_size -= 1;
        edit_suppr(buff->buffer, buff->cursor_position, buff->buff_size);
    }
    return EXECUTED;
}

static int backward_delete_key(buffer_t *buff, char c)
{
    if (c != BACK_DEL)
        return CONTINUE;
    if (buff->cursor_position > BEGINNING) {
        memmove(&buff->buffer[buff->cursor_position - 1],
        &buff->buffer[buff->cursor_position],
        buff->buff_size - buff->cursor_position + 1);
        putchar('\b');
        buff->cursor_position -= 1;
        buff->buff_size -= 1;
        edit_delete(buff->buffer, buff->cursor_position, buff->buff_size);
    }
    return EXECUTED;
}

static void check_user_input(buffer_t *buff)
{
    size_t i = 0;
    int return_value = 0;
    int c = 0;

    while (1) {
        c = getchar();
        while (return_value != EXECUTED && i < LIMIT) {
            return_value = (user_char[i])(buff, c);
            i += 1;
        }
        i = 0;
        return_value = 0;
        if (c == '\n' || c == LIMIT)
            break;
    }
    if (c == LIMIT)
        buff->buff_size = -1;
    return;
}

int edit_input(char **input)
{
    struct termios raw;
    struct termios original;
    buffer_t buff = {0};

    enable_icanon(&raw, &original);
    check_user_input(&buff);
    put_return(buff.cursor_position, buff.buff_size);
    if (buff.buff_size != -1)
        *input = strdup(buff.buffer);
    disable_icanon(&original);
    return buff.buff_size;
}
