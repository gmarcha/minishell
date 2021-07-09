/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 02:53:59 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/05 02:53:59 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_command(t_cmd *cmd, size_t nb_cmd, size_t index_cmd,
	int p_fd[])
{
	if (index_cmd < nb_cmd - 1)
	{
		if (pipe(p_fd) == -1)
		{
			p_error(PROGRAM_NAME, "pipe()", errno);
			close_cmd_fd(cmd, nb_cmd);
			return (-1);
		}
		cmd[index_cmd].fd_out = p_fd[1];
		cmd[index_cmd + 1].fd_in = p_fd[0];
	}
	return (0);
}

static int	init_command(t_cmd *cmd, size_t nb_cmd, size_t index_cmd,
	int exit_status)
{
	int				p_fd[2];

	if (pipe_command(cmd, nb_cmd, index_cmd, p_fd) == -1)
		return (-1);
	cmd[index_cmd].save_stdin = dup(STDIN_FILENO);
	if (cmd[index_cmd].save_stdin == -1)
	{
		p_error(PROGRAM_NAME, "dup()", errno);
		close_cmd_fd(cmd, nb_cmd);
		return (-1);
	}
	cmd[index_cmd].save_stdout = dup(STDOUT_FILENO);
	if (cmd[index_cmd].save_stdout == -1)
	{
		p_error(PROGRAM_NAME, "dup()", errno);
		close_cmd_fd(cmd, nb_cmd);
		return (-1);
	}
	return (redirect(cmd, nb_cmd, index_cmd, exit_status));
}

static int	init_process(t_cmd *cmd, size_t nb_cmd, size_t index_cmd,
	char **envp)
{
	pid_t			pid;

	pid = fork();
	if (pid == -1)
	{
		p_error(PROGRAM_NAME, "fork()", errno);
		close_cmd_fd(cmd, nb_cmd);
		return (-1);
	}
	else if (pid == 0)
		execute(cmd, nb_cmd, index_cmd, envp);
	else
	{
		if (reset_redirection(cmd, nb_cmd, index_cmd) == -1)
			return (-1);
		cmd[index_cmd].pid_process = pid;
	}
	return (0);
}

int	launch(t_cmd *cmd, size_t nb_cmd, char **envp, int exit_status)
{
	size_t			index_cmd;
	int				ret;

	index_cmd = 0;
	while (index_cmd < nb_cmd)
	{
		ret = init_command(cmd, nb_cmd, index_cmd, exit_status);
		if (ret == -1)
			return (1);
		if (ret == -2)
			continue ;
		ret = launch_builtin(cmd, nb_cmd, index_cmd, envp);
		if (ret == -1)
			return (1);
		else if (ret >= 0)
			continue ;
		ret = init_process(cmd, nb_cmd, index_cmd, envp);
		if (ret == -1)
			return (1);
		index_cmd++;
	}
	close_cmd_fd(cmd, nb_cmd);
	return (wait_process(cmd, nb_cmd));
}
