/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:44:31 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/15 14:44:31 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_env_variable(char *line, t_var *env, int heredoc_fd[], size_t i)
{
	char			*replace_str;
	char			*var_env;
	int				size;

	size = ft_strclen(line + i, "$|<>'\"");
	var_env = ft_substr(line + i, 0, size);
	if (var_env == NULL)
	{
		free(line);
		return (-1);
	}
	replace_str = get_var(env, var_env);
	ft_putstr_fd(replace_str, heredoc_fd[1]);
	return (size);
}

static char	*write_line(char *line, t_var *env, int exit_status, int heredoc_fd[])
{
	int				size;
	size_t			i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && (ft_ischarset(line[i + 1], "?_") || ft_isalpha(line[i + 1]) == 1))
		{
			if (line[++i] == '?')
			{
				ft_putnbr_fd(exit_status, heredoc_fd[1]);
				i++;
			}
			else
			{
				size = write_env_variable(line, env, heredoc_fd, i);
				if (size == -1)
					return (NULL);
				i += size;
			}
		}
		else
			ft_putchar_fd(line[i++], heredoc_fd[1]);
	}
	return (line);
}

int	heredoc(t_cmd *cmd, size_t index_cmd, t_var *env, int exit_status)
{
	int				heredoc_fd[2];
	char			*line;

	if (pipe(heredoc_fd) == -1)
		return (-1);
	line = NULL;
	line = line_read(line, "> ");
	while (line != NULL && ft_strcmp(line, cmd[index_cmd].name_in) != 0)
	{
		if (write_line(line, env, exit_status, heredoc_fd) == NULL)
			return (-1);
		write(heredoc_fd[1], "\n", 1);
		line = line_read(line, "> ");
	}
	if (line != NULL)
		free(line);
	else
		write(1, "\n", 1);
	close(heredoc_fd[1]);
	return (heredoc_fd[0]);
}
