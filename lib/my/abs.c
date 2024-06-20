/*
** EPITECH PROJECT, 2024
** val_abs.c
** File description:
** val_abs
*/

int my_abs(int nb)
{
    int result = nb;

    if (result < 0)
        result *= -1;
    return result;
}

long my_labs(long nb)
{
    long result = nb;

    if (result < 0)
        result *= -1;
    return result;
}

long long my_llabs(long long nb)
{
    long long result = nb;

    if (result < 0)
        result *= -1;
    return result;
}
