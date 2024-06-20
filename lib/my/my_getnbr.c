/*
** EPITECH PROJECT, 2023
** my_getnbr.c
** File description:
** my get number
*/
#include "mysh.h"

int end(int nb, int nb_less)
{
    if ((nb_less % 2 == 0) && (nb_less != 0))
        nb = nb * -1;
    nb = nb / 10;
    return nb;
}

int my_getnbr(char const *str)
{
    int nb = 0;
    int nb_less = 0;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] != '-' || str[i] != '+') &&
            ((str[i] < '0' || str[i] > '9')))
            return -1;
        if (my_strlen(str) == 0 && str[i] == '-')
            nb_less++;
        if (str[i] >= '0' && str[i] <= '9') {
            nb = nb + (str[i] - 48);
            nb = nb * 10;
        }
        if (nb > 0 && (str[i] < '0' || str[i] > '9'))
            break;
    }
    nb = end(nb, nb_less);
    return nb;
}
