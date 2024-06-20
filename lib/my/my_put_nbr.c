/*
** EPITECH PROJECT, 2023
** my_put_nbr.c
** File description:
** my_putnbr
*/
#include "mysh.h"

void my_put_nbr(int nb)
{
    int rest = 0;

    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    if (nb >= 0 && nb <= 9) {
        my_putchar(nb + 48);
    } else {
        rest = nb % 10;
        nb = nb / 10;
        my_put_nbr(nb);
        my_putchar(rest + 48);
    }
    return;
}
