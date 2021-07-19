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

volatile int	g_exit_status = 0;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
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

static int	minishell_init(t_var **env)
{
	char		*pwd;

	if (*(char *)get_var(*env, "PWD") == '\0')
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			clear_list(env);
			return (EXIT_FAILURE);
		}
		if (add_var(env, "PWD", pwd) == FALSE)
		{
			free(pwd);
			clear_list(env);
			return (EXIT_FAILURE);
		}
		if (add_var(env, "OLDPWD", pwd) == FALSE)
		{
			free(pwd);
			clear_list(env);
			return (EXIT_FAILURE);
		}
		free(pwd);
	}
	return (EXIT_SUCCESS);
}

static void	minishell_loop(t_var **env)
{
	char			*line;
	t_cmd			*cmd;

	line = NULL;
	line = line_read(line, PROMPT);
	while (line != NULL)
	{
		cmd = parse_line(&line, *env);
		if (cmd != NULL)
		{
			g_exit_status = launch(cmd, env, g_exit_status);
			free_cmd(cmd, cmd[0].nb_cmd);
		}
		line = line_read(line, PROMPT);
	}
}

int	main(int ac, char *av[], char **envp)
{
	t_var			*env;

	(void)ac;
	(void)av;
	if (sig_init() == 0)
		return (EXIT_FAILURE);
	env = construct_globals(envp);
	if (*(char *)get_var(env, "PATH") == '\0')
	{
		if (add_var(&env, "PATH", DEFAULT_PATH) == FALSE)
		{
			clear_list(&env);
			return (EXIT_FAILURE);
		}
	}
	if (minishell_init(&env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	minishell_loop(&env);
	ft_putstr_fd("exit\n", 2);
	clear_list(&env);
	return (g_exit_status);
}
