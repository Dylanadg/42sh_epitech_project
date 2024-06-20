/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** icanon.c
*/
#include <termios.h>
#include <unistd.h>

void enable_icanon(struct termios *raw, struct termios *original)
{
    tcgetattr(STDIN_FILENO, original);
    *raw = *original;
    tcgetattr(STDIN_FILENO, raw);
    raw->c_lflag &= ~(ICANON | ECHO);
    raw->c_cc[VMIN] = 1;
    raw->c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, raw);
}

void disable_icanon(struct termios *original)
{
    tcsetattr(STDIN_FILENO, TCSANOW, original);
}
