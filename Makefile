NAME		=	minishell
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
INC			=	-I ./inc
OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))
SRC			=	src/ft_free_strs.c \
				src/ft_ischarset.c \
				src/ft_strclen.c \
				src/ft_strlcpy.c \
				src/minishell.c \
				src/shell_line.c \
				src/shell_split.c \
				src/utils.c

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -fsanitize=address -o $@ $^

obj/%.o:	src/%.c
			$(CC) $(FLAGS) $(INC) -o $@ -c $<

run:
			@$(CC) $(FLAGS) $(INC) $(SRC)
			@./a.out
			@rm -rf a.out

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(OBJ)

re:			fclean all

.PHONY:		all run clean fclean re