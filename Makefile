NAME		=	minishell
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
INC			=	-I ./inc -I ./libft
libft		=	-L ./libft -lft
OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))
SRC			=	src/ft_free_strs.c \
				src/ft_ischarset.c \
				src/ft_strclen.c \
				src/minishell.c \
				src/shell_line.c \
				src/shell_split.c

all:		$(NAME)

$(NAME):	$(OBJ)
			make -C libft
			$(CC) $(FLAGS) -fsanitize=address -o $@ $^ -L ./libft -lft

obj/%.o:	src/%.c
			$(CC) $(FLAGS) $(INC) -o $@ -c $<

run:
			@$(CC) $(FLAGS) $(INC) $(SRC)
			@./a.out
			@rm -rf a.out

clean:
			make $@ -C libft
			rm -rf $(OBJ)

fclean:		clean
			make $@ -C libft
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all run clean fclean re