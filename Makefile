NAME		=	minishell
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror
LFT			=	libft/libft.a
INC			=	-I ./inc -I ./libft
LIB			=	-L ./libft -lft -lreadline
OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))
SRC			=	src/close_cmd_fd.c \
				src/destroy_process.c \
				src/die.c \
				src/execute_path.c \
				src/execute.c \
				src/launch_builtin.c \
				src/launch.c \
				src/line_read.c \
				src/minishell.c \
				src/redirect.c \
				src/reset_redirection.c \
				src/wait_process.c

all:		$(LFT) obj $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -fsanitize=address -o $@ $^ $(LIB)

test:		test_launch

test_minishell:	all
			./minishell

test_launch:	$(OBJ) main_launch.o
			$(CC) $(CFLAGS) -fsanitize=address -o test_launch $^ $(LIB)
			@./test_launch
			@rm test_launch main_launch.o

%.o:		%.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(LFT):		
			@echo " [ .. ] | Compiling libft.."
			@make -sC libft
			@echo " [ OK ] | Libft ready!"

obj:
			@mkdir -p obj

obj/%.o:	src/%.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
			@make $@ -sC libft
			@rm -rf $(OBJ) obj
			@echo "clean: object files removed."

fclean:		clean
			@make $@ -sC libft
			@rm -rf $(NAME)
			@echo "fclean: binary files removed."

re:			fclean all

.PHONY:		all clean fclean re