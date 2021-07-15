NAME		=	minishell
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror
DEBUG		=	-fsanitize=address
LFT			=	libft/libft.a
INC			=	-I ./inc -I ./libft
LIB			=	-L ./libft -lft -lreadline
OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))
SRC			=	src/builtin_cd.c \
				src/builtin_echo.c \
				src/builtin_env.c \
				src/builtin_exit.c \
				src/builtin_export_extra.c \
				src/builtin_export.c \
				src/builtin_pwd.c \
				src/builtin_unset.c \
				src/close_cmd_fd.c \
				src/destroy_process.c \
				src/die.c \
				src/envs_destroy.c \
				src/envs_envp.c \
				src/envs_init.c \
				src/envs_var.c \
				src/execute_builtin.c \
				src/execute_path.c \
				src/execute.c \
				src/free_cmd.c \
				src/free_sstrs.c \
				src/launch_builtin.c \
				src/launch_redirect.c \
				src/launch_reset_redirection.c \
				src/launch_wait_process.c \
				src/launch.c \
				src/line_read.c \
				src/minishell.c \
				src/parse_add_arg_to_args.c \
				src/parse_command.c \
				src/parse_create_command.c \
				src/parse_expand_line.c \
				src/parse_expand_redirect_op.c \
				src/parse_handle_unclosed_quotes.c \
				src/parse_is_line_not_empty.c \
				src/parse_line.c \
				src/parse_remove_quotes.c \
				src/parse_skip_quotes.c \
				src/parse_split_command.c \
				src/parse_split_line.c

all:		$(LFT) obj $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(DEBUG) -o $@ $^ $(LIB)

test:		test_launch

test_minishell:	all
			./minishell

test_launch:	$(OBJ) main_launch.o
			$(CC) $(CFLAGS) -fsanitize=address -o test_launch $^ $(LIB)
			@./test_launch
			@rm test_launch main_launch.o

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