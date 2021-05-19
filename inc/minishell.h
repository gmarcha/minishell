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

int			shell_line(int fd, char **line);

char		**shell_split(const char *str, const char *charset);

#endif