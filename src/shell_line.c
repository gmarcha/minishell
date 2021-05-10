#include "minishell.h"

char	*fill_buffer(char **s, char *buf)
{
	char			*tmp;

	if (*s)
	{
		tmp = ft_strjoin(*s, buf);
		free(*s);
		*s = tmp;
		if (*s == 0)
			return (0);
	}
	else
	{
		*s = ft_strdup(buf);
		if (*s == 0)
			return (0);
	}
	return (*s);
}

int	fill_line(char **s, char **line)
{
	char			*tmp;
	int				len;

	len = ft_strclen(*s, "\n");
	*line = ft_substr(*s, 0, len);
	if ((*s)[len] == 0)
	{
		free(*s);
		*s = 0;
		return (0);
	}
	tmp = ft_strdup(*s + len + 1);
	free(*s);
	*s = tmp;
	if (*s == 0)
		return (-1);
	if (*s[0] == 0)
	{
		free(*s);
		*s = 0;
	}
	return (1);
}

int	read_file(int fd, char **line)
{
	static char		*s;
	char			buf[BUFFER_SIZE + 1];
	int				ret;

	while (1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buf[ret] = 0;
		s = fill_buffer(&s, buf);
		if (s == 0)
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret == -1)
		return (-1);
	if (s == 0 && ret == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	return (fill_line(&s, line));
}

int	shell_line(int fd, char **line)
{
	if (fd == -1 || line == 0)
		return (-1);
	return (read_file(fd, line));
}
