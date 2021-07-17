/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 23:33:29 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/05 23:33:29 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_file(char **filename, t_var *env)
{
	char			*expanse;
	char			*tmp;

	expanse = expand_line(*filename, env, g_exit_status);
	if (expanse == NULL)
		return (NULL);
	if (*expanse == '\0' || ft_strchr(expanse, ' ') != NULL)
	{
		tmp = ft_strjoin(*filename, ": ambiguous redirect");
		if (tmp == NULL)
		{
			free(expanse);
			return (NULL);
		}
		p_error(PROGRAM_NAME, tmp, 0);
		g_exit_status = 1;
		free(tmp);
		free(expanse);
		return (NULL);
	}
	free(*filename);
	*filename = expanse;
	return (*filename);
}

static int	redirect_input(t_cmd *cmd, size_t index_cmd, t_var *env,
	int exit_status)
{
	if (cmd[index_cmd].redirect_in != NO_REDIRECTION)
	{
		if (cmd[index_cmd].redirect_in == SIMPLE_REDIRECTION)
		{
			if (expand_file(&cmd[index_cmd].name_in, env) == NULL)
				return (-2);
		}
		if (remove_quotes(&cmd[index_cmd].name_in) == -1)
			return (-1);
		if (cmd[index_cmd].fd_in != STDIN_FILENO)
			close(cmd[index_cmd].fd_in);
		if (cmd[index_cmd].redirect_in == SIMPLE_REDIRECTION)
			cmd[index_cmd].fd_in = open(cmd[index_cmd].name_in, O_RDONLY);
		else if (cmd[index_cmd].redirect_in == DOUBLE_REDIRECTION)
			cmd[index_cmd].fd_in = heredoc(cmd, index_cmd, env, exit_status);
		if (cmd[index_cmd].fd_in == -1)
		{
			p_error(PROGRAM_NAME, cmd[index_cmd].name_in, errno);
			return (-2);
		}
	}
	if (index_cmd != 0 || cmd[index_cmd].redirect_in != NO_REDIRECTION)
		if (dup2(cmd[index_cmd].fd_in, STDIN_FILENO) == -1)
			return (-1);
	return (0);
}

static int	redirect_output(t_cmd *cmd, size_t nb_cmd, size_t index_cmd, t_var *env)
{
	if (cmd[index_cmd].redirect_out != NO_REDIRECTION)
	{
		if (expand_file(&cmd[index_cmd].name_out, env) == NULL)
			return (-2);
		if (remove_quotes(&cmd[index_cmd].name_out) == -1)
			return (-1);
		if (cmd[index_cmd].fd_out != STDOUT_FILENO)
			close(cmd[index_cmd].fd_out);
		if (cmd[index_cmd].redirect_out == SIMPLE_REDIRECTION)
			cmd[index_cmd].fd_out = open(cmd[index_cmd].name_out,
					O_CREAT | O_WRONLY | O_TRUNC, 0664);
		else if (cmd[index_cmd].redirect_out == DOUBLE_REDIRECTION)
			cmd[index_cmd].fd_out = open(cmd[index_cmd].name_out,
					O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (cmd[index_cmd].fd_out == -1)
		{
			p_error(PROGRAM_NAME, cmd[index_cmd].name_out, errno);
			return (-2);
		}
	}
	if (index_cmd < nb_cmd - 1 || cmd[index_cmd].redirect_out != NO_REDIRECTION)
	{
		if (dup2(cmd[index_cmd].fd_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	redirect(t_cmd *cmd, size_t index_cmd, t_var **env, int exit_status)
{
	int				ret;

	ret = redirect_input(cmd, index_cmd, *env, exit_status);
	if (ret != 0)
	{
		if (ret == -1)
			close_cmd_fd(cmd, cmd[0].nb_cmd);
		return (ret);
	}
	ret = redirect_output(cmd, cmd[0].nb_cmd, index_cmd, *env);
	if (ret != 0)
	{
		if (ret == -1)
			close_cmd_fd(cmd, cmd[0].nb_cmd);
		return (ret);
	}
	return (0);
}
