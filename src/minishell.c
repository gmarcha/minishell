/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:51:34 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/05 16:51:34 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

int	sig_init(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		return (0);
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		return (0);
	return (1);
}

static char	*handle_unclosed_quotes(char *line)
{
	size_t			status;
	size_t			pos;
	size_t			i;

	status = 0;
	pos = ft_strlen(line);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			pos = i++;
			status = 1;
			while (line[i] != '\0')
			{
				if (line[i++] == '\'')
				{
					status = 0;
					break ;
				}
			}
			if (status == 1)
				break ;
		}
		else if (line[i] == '"')
		{
			pos = i++;
			status = 1;
			while (line[i] != '\0')
			{
				if (line[i++] == '"')
				{
					status = 0;
					break ;
				}
			}
			if (status == 1)
				break ;
		}
		i++;
	}
	if (status == 0)
		return (ft_strdup(line));
	return (ft_substr(line, 0, pos));
}

char	*expand_line(char *line_content)
{
	printf("%s\n", line_content);
	return (line_content);
}

t_cmd	*parse_line(char *line, size_t *nb_cmd)
{
	char			*line_content;
	char			*line_expand;

	(void)nb_cmd;
	line_content = handle_unclosed_quotes(line);
	if (line_content == NULL)
		return (NULL);
	line_expand = expand_line(line_content);
	exit(0);
}

int	main(int ac, char *av[], char **envp)
{
	t_cmd			*cmd;
	size_t			nb_cmd;
	char			*line;
	int				exit_status;

	(void)ac; (void)av;
	if (sig_init() == 0)
		return (0);
	exit_status = 0;
	line = NULL;
	line = line_read(line, "$> ");
	while (line != NULL)
	{
		nb_cmd = 0;
		cmd = parse_line(line, &nb_cmd);
		exit_status = launch(cmd, nb_cmd, envp, exit_status);
		// free_cmd(cmd, nb_cmd);
		line = line_read(line, "$> ");
	}
	ft_putstr_fd("exit\n", 1);
	return (exit_status);
}
