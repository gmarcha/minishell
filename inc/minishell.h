#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "libft.h"

# define BUFFER_SIZE	4096

void		*ft_free_strs(char **strs);
int			ft_ischarset(int c, const char *charset);
size_t		ft_strclen(const char *s, const char *charset);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);

int			ft_strlen(const char *s);
char		*ft_strchr(char *s, int c);
char		*ft_strdup(char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_substr(char *s, unsigned int start, unsigned int len);

int			shell_line(int fd, char **line);

char		**shell_split(const char *str, const char *charset);

#endif