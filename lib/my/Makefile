##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC		=	my_str_to_word_array.c	\
			my_array_to_str.c		\
			delete_in_list.c		\
			is_maj_alpha.c			\
			is_min_alpha.c			\
			my_put_float.c			\
			my_put_array.c			\
			is_alphanum.c			\
			create_node.c			\
			mini_printf.c			\
			my_arraylen.c			\
			my_strncmp.c			\
			my_put_nbr.c			\
			my_putchar.c			\
			my_putstr.c				\
			my_getnbr.c				\
			my_strdup.c				\
			my_strcat.c				\
			my_strcmp.c				\
			my_strlen.c				\
			is_alpha.c				\
			is_digit.c				\
			free_all.c				\
			abs.c					\

OBJ		=	$(SRC:.c=.o)

NAME	=	../libmy.a

CFLAGS	=	-Wall -Wextra

CPPFLAGS=	-I./../../include -g3

all:		$(NAME)

debug:	CFLAGS += g3

debug:	re

$(NAME):	$(OBJ)
			ar rc -o $(NAME) $(OBJ)

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re debug
