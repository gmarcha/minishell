NAME		= libft.a
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
OBJ			= $(SRC:.c=.o)
SRC			= 	free_index.c \
				free_mem_alloc.c \
				free_wrap.c \
				ft_atoi_base.c \
				ft_atoi.c \
				ft_atol.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_convert_base.c \
				ft_csplit.c \
				ft_free_strs.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_ischarset.c \
				ft_isdigit.c \
				ft_islower.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_isupper.c \
				ft_itoa_base.c \
				ft_itoa.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdel_front.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_nbrlen_base.c \
				ft_nbrlen.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strclen.c \
				ft_strcmp.c \
				ft_strconcat.c \
				ft_strcpy.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strsjoin.c \
				ft_strslen.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				get_index.c \
				malloc_clear.c \
				malloc_destroy.c \
				malloc_index.c \
				malloc_wrap.c

all:		$(NAME)

$(NAME):	$(OBJ)
			ar rcs $@ $^

%.o:		%.c
			$(CC) $(FLAGS) -o $@ -c $<

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
