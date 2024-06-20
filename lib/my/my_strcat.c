/*
** EPITECH PROJECT, 2023
** my_strcat.c
** File description:
** my_strcat
*/
#include "mysh.h"

char *my_strcat(char *dest, char const *src)
{
    int max_d = 0;
    char *temp = my_strdup(dest);
    int size_dest = my_strlen(dest);
    int size_src = my_strlen(src);

    if (dest != NULL)
        free(dest);
    dest = malloc(sizeof(char) * (size_dest + size_src + 1));
    if (temp != NULL)
        for (int i = 0; temp[i] != '\0'; ++i) {
            dest[max_d] = temp[i];
            max_d++;
        }
    if (src != NULL)
        for (int i = 0; src[i] != '\0'; ++i) {
            dest[max_d] = src[i];
            max_d++;
        }
    dest[max_d] = '\0';
    return dest;
}

char *my_strcat_nofree(char *dest, char const *src)
{
    int max_d = 0;
    char *temp = my_strdup(dest);
    int size_dest = my_strlen(dest);
    int size_src = my_strlen(src);
    char *dst = malloc(sizeof(char) * (size_dest + size_src + 1));

    for (int i = 0; temp[i] != '\0'; ++i) {
        dst[max_d] = temp[i];
        max_d++;
    }
    for (int i = 0; src[i] != '\0'; ++i) {
        dst[max_d] = src[i];
        max_d++;
    }
    dst[max_d] = '\0';
    free(temp);
    return dst;
}

static void modify_string(const char *str, const char *src,
    char **dest, size_t *max_d)
{
    if (str != NULL)
        for (size_t i = 0; str[i] != '\0'; ++i) {
            (*dest)[*max_d] = str[i];
            *max_d += 1;
        }
    if (src != NULL)
        for (size_t i = 0; src[i] != '\0'; ++i) {
            (*dest)[*max_d] = src[i];
            *max_d += 1;
        }
}

bool my_strcat_mod(char **dest, char const *src)
{
    size_t max_d = 0;
    char *str = my_strdup((const char *)*dest);
    size_t size_dest = my_strlen(*dest);
    size_t size_src = my_strlen(src);

    free(*dest);
    *dest = malloc(sizeof(char) * (size_dest + size_src + 1));
    if (*dest == NULL)
        return false;
    modify_string(str, src, dest, &max_d);
    (*dest)[max_d] = '\0';
    free(str);
    return true;
}
