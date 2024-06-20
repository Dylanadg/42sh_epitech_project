##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC		=	src/main.c												\
			src/sh.c												\
			src/alias.c												\
			src/commands/cd.c										\
			src/commands/env.c										\
			src/commands/echo.c										\
			src/array_to_env.c										\
			src/divide_commands.c									\
			src/execution/execute.c									\
			src/redirections/pipe.c									\
			src/edit_input/icanon.c									\
			src/errors/error_in_exec.c								\
			src/edit_input/edit_input.c								\
			src/path_handling/is_path.c								\
			src/errors/error_in_input.c								\
			src/errors/error_in_command.c							\
			src/edit_input/handle_string.c							\
			src/path_handling/get_paths.c							\
			src/verifications/is_a_binary.c							\
			src/verifications/failed_malloc.c						\
			src/verifications/verif_arrow_pipe.c 					\
			src/verifications/is_in_current_dir.c					\
			src/redirections/verifications/is_pipe.c				\
			src/redirections/verifications/is_arrow.c				\
			src/redirections/verifications/is_and_and.c 			\
			src/redirections/arrows/write_until_word.c				\
			src/redirections/arrows/redirect_to_file.c				\
			src/redirections/arrows/redirect_to_binary.c			\
			src/redirections/arrows/arrows_redirection.c			\
			src/redirections/verifications/is_redirection.c			\
			src/redirections/verifications/has_redirection.c		\
			src/redirections/verifications/valid_commands_sequence.c\

TEST	=	tests/unitests.c										\
			tests/functionnal_tests.c								\
			src/sh.c												\
			src/alias.c												\
			src/commands/cd.c										\
			src/commands/env.c										\
			src/commands/echo.c										\
			src/array_to_env.c										\
			src/divide_commands.c									\
			src/execution/execute.c									\
			src/redirections/pipe.c									\
			src/errors/error_in_exec.c								\
			src/edit_input/icanon.c									\
			src/edit_input/edit_input.c								\
			src/path_handling/is_path.c								\
			src/errors/error_in_input.c								\
			src/errors/error_in_command.c							\
			src/path_handling/get_paths.c							\
			src/edit_input/handle_string.c							\
			src/verifications/is_a_binary.c							\
			src/verifications/failed_malloc.c						\
			src/verifications/is_in_current_dir.c					\
			src/redirections/verifications/is_pipe.c				\
			src/redirections/verifications/is_arrow.c				\
			src/redirections/arrows/write_until_word.c				\
			src/redirections/arrows/redirect_to_file.c				\
			src/redirections/arrows/redirect_to_binary.c			\
			src/redirections/arrows/arrows_redirection.c			\
			src/redirections/verifications/is_redirection.c			\
			src/redirections/verifications/has_redirection.c		\
			src/redirections/verifications/valid_commands_sequence.c\


OBJ		=	$(SRC:.c=.o)

NAME	=	42sh

TESTNAME=	unit_tests

LIB		=	lib/my/

CFLAGS	=	-Wall -Wextra -g

CPPFLAGS=	-I./include

all:		$(NAME)

$(NAME):	$(OBJ)
			make -C $(LIB)
			$(CC) -o $(NAME) $(OBJ) -Llib/ -lmy

debug:	CFLAGS += -g3

debug:	$(NAME)

coverage:
			gcovr --exclude tests/

tests_run:
			make -C $(LIB)
			$(CC) -o $(TESTNAME) $(TEST) -Llib/ -lmy -lcriterion --coverage \
			$(CPPFLAGS)
			./unit_tests

clean:
			make clean -C $(LIB)
			rm -rf $(OBJ)

fclean_test:
			rm -rf $(TESTNAME)

fclean_coverage:	fclean_test
		rm -rf *.gcda *.gcno

fclean_all: fclean_coverage fclean

fclean:
			make fclean -C $(LIB)
			rm -rf $(OBJ)
			rm -rf $(NAME)

fclean_all: fclean_coverage fclean_test fclean

style:
			coding-style . .
			cat coding-style-reports.log
			rm -rf coding-style-reports.log

re:			fclean all

re_test:	fclean_test tests_run unitests

.PHONY:		all clean fclean re debug tests_run fclean_test fclean_coverage\
			style fclean_all
