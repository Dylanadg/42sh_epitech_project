/*
** EPITECH PROJECT, 2023
** my_printf
** File description:
** print float
*/

#include "mysh.h"

void my_put_float(float a)
{
    int firpart;
    int secpart;

    firpart = a;
    if (firpart < 0) {
        secpart = (((a * 100) - firpart * 100) * -1);
    } else {
        secpart = (a * 100) - firpart * 100;
    }
    my_put_nbr(firpart);
    my_putchar('.');
    my_put_nbr(secpart);
    if (secpart == 0)
        my_putchar('0');
    return;
}
