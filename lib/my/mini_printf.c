/*
** EPITECH PROJECT, 2023
** mini_printf.c
** File description:
** mini printf project solo
*/
#include <stdlib.h>
#include <stdarg.h>
#include "mysh.h"

int cmp_nbr(int nb)
{
    int count = 1;

    if (nb < 0) {
        count ++;
        nb = nb * -1;
    }
    while (nb >= 10) {
        nb = nb / 10;
        count ++;
    }
    return count;
}

void verif_percent_2(const char *format, va_list ap, int *nb_print, int i)
{
    float flo = 0;

    switch (format[i + 1]) {
    case ('c') :
        my_putchar(va_arg(ap, int));
        *nb_print += 1;
        break;
    case ('%') :
        my_putchar('%');
        nb_print += 1;
        break;
    case ('f') :
        flo = va_arg(ap, double);
        my_put_float(flo);
        nb_print += 4;
        break;
    default:
        my_putchar(format[i]);
        my_putchar(format[i + 1]);
    }
}

int verif_percent(const char *format, va_list ap, int nb_print, int i)
{
    char *var;
    int intgr;

    switch (format[i + 1]) {
    case ('d') :
    case ('i') :
        intgr = va_arg(ap, int);
        my_put_nbr(intgr);
        nb_print = nb_print + cmp_nbr(intgr);
        break;
    case ('s') :
        var = va_arg(ap, char *);
        my_putstr(var);
        nb_print = nb_print + my_strlen(var);
        break;
    default:
        verif_percent_2(format, ap, &nb_print, i);
        nb_print++;
    }
    return nb_print;
}

int mini_printf(const char *format, ...)
{
    int nb_print = 0;
    va_list ap;

    va_start(ap, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            nb_print = verif_percent(format, ap, nb_print, i);
            i ++;
            continue;
        }
        nb_print++;
        my_putchar(format[i]);
    }
    va_end(ap);
    return nb_print;
}
