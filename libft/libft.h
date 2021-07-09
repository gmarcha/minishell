#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef unsigned int	t_bool;

typedef enum e_bool_value
{
	FALSE,
	TRUE
}				t_bool_value;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_btree
{
	void			*content;
	struct s_btree	*left;
	struct s_btree	*right;
}				t_btree;

typedef struct s_rbtree
{
	void			*content;
	int				color;
	struct s_rbtree	*parent;
	struct s_rbtree	*left;
	struct s_rbtree	*right;
}					t_rbtree;

typedef struct s_mem_alloc
{
	void		*content;
	void		(*content_free)();
	const char	*name;
}				t_mem_alloc;

void	btree_apply_infix(t_btree *node, void (*apply_f)(void *));
void	btree_apply_prefix(t_btree *node, void (*apply_f)(void *));
void	btree_apply_suffix(t_btree *node, void (*apply_f)(void *));
void	btree_clear(t_btree *node, void (*del)(void *));
t_btree	*btree_create_node(void *content);
t_btree	*btree_insert_data(
			t_btree **node, void *content, int (*cmp_f)(void *, void *));
void	*btree_search_data(
			t_btree *node, void *data_ref, int (*cmp_f)(void *, void *));
void	free_index(t_list **mem_ref, const char *name);
void	free_mem_alloc(void *mem_alloc);
void	free_wrap(t_list **mem_ref, void *content);
int		ft_atoi_base(const char *str, const char *base, size_t len_base);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_convert_base(
			const char *str, const char *base_from, const char *base_to);
void	ft_free_strs(void *strs);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_ischarset(int c, const char *charset);
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
char	*ft_itoa_base(int n, const char *base, size_t len_base);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdel_front(t_list **alst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_nbrlen(int n);
size_t	ft_nbrlen_base(int n, size_t len_base);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strchr(const char *s, int c);
size_t	ft_strclen(const char *s, const char *charset);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strconcat(char **str, char *new);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strsjoin(const char **strs, const char *sep);
size_t	ft_strslen(const char **strs);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	*get_index(t_list **mem_ref, const char *name);
void	malloc_clear(t_list **mem_ref);
void	malloc_destroy(t_list **global_ref, t_list **local_ref);
void	*malloc_index(
			t_list **mem_ref,
			const char *name, void (*mem_free)(void *), void *content);
void	*malloc_wrap(
			t_list **mem_ref,
			const char *name, void (*mem_free)(void *), size_t size);

#endif
