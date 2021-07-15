/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:51:34 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/15 17:26:24 by gamarcha         ###   ########.fr       */
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

static void	minishell_loop(t_var **env, int *exit_status)
{
	char			*line;
	t_cmd			*cmd;

	line = NULL;
	line = line_read(line, PROMPT);
	while (line != NULL)
	{
		cmd = parse_line(&line, *env, exit_status);
		if (cmd != NULL)
		{
			*exit_status = launch(cmd, env, *exit_status);
			free_cmd(cmd, cmd[0].nb_cmd);
		}
		line = line_read(line, PROMPT);
	}
}

int	main(int ac, char *av[], char **envp)
{
	t_var			*env;
	int				exit_status;

	(void)ac;
	(void)av;
	if (sig_init() == 0)
		return (EXIT_FAILURE);
	env = construct_globals(envp);
	if (env == NULL)
		return (EXIT_FAILURE);
	exit_status = 0;
	minishell_loop(&env, &exit_status);
	ft_putstr_fd("exit\n", 2);
	clear_list(&env);
	return (exit_status);
}
