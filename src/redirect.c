/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 23:33:29 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/05 23:33:29 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc(t_cmd *cmd, size_t index_cmd, int exit_status)
// TODO: expansion on write();
{
	int				heredoc_fd[2];
	char			*line;

	if (pipe(heredoc_fd) == -1)
		return (-1);
	line = NULL;
	line = line_read(line, "> ");
	(void)exit_status;
	while (line != NULL && ft_strcmp(line, cmd[index_cmd].name_in) != 0)
	{
		write(heredoc_fd[1], line, ft_strlen(line));
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

static int	redirect_input(t_cmd *cmd, size_t index_cmd, int exit_status)
{
	if (cmd[index_cmd].redirect_in != NO_REDIRECTION)
	{
		if (cmd[index_cmd].fd_in != STDIN_FILENO)
			close(cmd[index_cmd].fd_in);
		if (cmd[index_cmd].redirect_in == SIMPLE_REDIRECTION)
			cmd[index_cmd].fd_in = open(cmd[index_cmd].name_in, O_RDONLY);
		else if (cmd[index_cmd].redirect_in == DOUBLE_REDIRECTION)
			cmd[index_cmd].fd_in = heredoc(cmd, index_cmd, exit_status);
		if (cmd[index_cmd].fd_in == -1)
			return (-2);
	}
	if (index_cmd != 0 || cmd[index_cmd].redirect_in != NO_REDIRECTION)
		if (dup2(cmd[index_cmd].fd_in, STDIN_FILENO) == -1)
			return (-1);
	return (0);
}

static int	redirect_output(t_cmd *cmd, size_t nb_cmd, size_t index_cmd)
{
	if (cmd[index_cmd].redirect_out != NO_REDIRECTION)
	{
		if (cmd[index_cmd].fd_out != STDOUT_FILENO)
			close(cmd[index_cmd].fd_out);
		if (cmd[index_cmd].redirect_out == SIMPLE_REDIRECTION)
			cmd[index_cmd].fd_out = open(cmd[index_cmd].name_out,
					O_CREAT | O_WRONLY | O_TRUNC, 0664);
		else if (cmd[index_cmd].redirect_out == DOUBLE_REDIRECTION)
			cmd[index_cmd].fd_out = open(cmd[index_cmd].name_out,
					O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (cmd[index_cmd].fd_out == -1)
			return (-2);
	}
	if (index_cmd < nb_cmd - 1 || cmd[index_cmd].redirect_out != NO_REDIRECTION)
	{
		if (dup2(cmd[index_cmd].fd_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	redirect(t_cmd *cmd, size_t nb_cmd, size_t index_cmd, int exit_status)
{
	int				ret;

	ret = redirect_input(cmd, index_cmd, exit_status);
	if (ret != 0)
	{
		p_error(PROGRAM_NAME, cmd[index_cmd].name_in, errno);
		if (ret == -1)
			close_cmd_fd(cmd, nb_cmd);
		return (ret);
	}
	ret = redirect_output(cmd, nb_cmd, index_cmd);
	if (ret != 0)
	{
		p_error(PROGRAM_NAME, cmd[index_cmd].name_out, errno);
		if (ret == -1)
			close_cmd_fd(cmd, nb_cmd);
		return (ret);
	}
	return (0);
}
