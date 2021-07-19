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

static int	is_ambiguous(char *expanse)
{
	size_t			i;

	i = 0;
	while (expanse[i] != '\0')
	{
		skip_quotes(expanse, &i);
		if (expanse[i] == ' ')
			return (-1);
		i++;
	}
	return (0);
}

static char	*expand_file(char **filename, t_var *env)
{
	char			*expanse;
	char			*tmp;

	expanse = expand_line(*filename, env, g_exit_status);
	if (expanse == NULL)
		return (NULL);
	if (*expanse == '\0' || is_ambiguous(expanse) == -1)
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

static int	redirect_input(t_cmd *cmd, size_t index_cmd, size_t i, t_var *env)
{
	if (cmd[index_cmd].redirect_op[i][1] == '\0')
	{
		if (expand_file(cmd[index_cmd].redirection + i, env) == NULL)
			return (-1);
	}
	if (remove_quotes(cmd[index_cmd].redirection + i) == -1)
		return (-1);
	if (cmd[index_cmd].fd_in != STDIN_FILENO)
		close(cmd[index_cmd].fd_in);
	if (cmd[index_cmd].redirect_op[i][1] == '\0')
		cmd[index_cmd].fd_in = open(cmd[index_cmd].redirection[i], O_RDONLY);
	else if (cmd[index_cmd].redirect_op[i][1] == '<')
		cmd[index_cmd].fd_in = heredoc(
				cmd[index_cmd].redirection[i], env, g_exit_status);
	if (cmd[index_cmd].fd_in == -1)
	{
		p_error(PROGRAM_NAME, cmd[index_cmd].redirection[i], errno);
		return (-1);
	}
	return (0);
}

static int	redirect_output(t_cmd *cmd, size_t index_cmd, size_t i, t_var *env)
{
	if (expand_file(cmd[index_cmd].redirection + i, env) == NULL)
		return (-1);
	if (remove_quotes(cmd[index_cmd].redirection + i) == -1)
		return (-1);
	if (cmd[index_cmd].fd_out != STDOUT_FILENO)
		close(cmd[index_cmd].fd_out);
	if (cmd[index_cmd].redirect_op[i][1] == '\0')
		cmd[index_cmd].fd_out = open(cmd[index_cmd].redirection[i],
				O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else if (cmd[index_cmd].redirect_op[i][1] == '>')
		cmd[index_cmd].fd_out = open(cmd[index_cmd].redirection[i],
				O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (cmd[index_cmd].fd_out == -1)
	{
		p_error(PROGRAM_NAME, cmd[index_cmd].redirection[i], errno);
		return (-1);
	}
	return (0);
}

int	redirect(t_cmd *cmd, size_t index_cmd, t_var **env)
{
	size_t			i;

	i = 0;
	while (cmd[index_cmd].redirection != NULL
		&& cmd[index_cmd].redirection[i] != NULL)
	{
		if (*cmd[index_cmd].redirect_op[i] == '<')
		{
			if (redirect_input(cmd, index_cmd, i, *env) != 0)
				return (-1);
		}
		else if (*cmd[index_cmd].redirect_op[i] == '>')
			if (redirect_output(cmd, index_cmd, i, *env) != 0)
				return (-1);
		i++;
	}
	if (index_cmd != 0 || cmd[index_cmd].redirection != NULL)
		if (dup2(cmd[index_cmd].fd_in, STDIN_FILENO) == -1)
			return (-1);
	if (index_cmd < cmd[0].nb_cmd - 1 || cmd[index_cmd].redirection != NULL)
		if (dup2(cmd[index_cmd].fd_out, STDOUT_FILENO) == -1)
			return (-1);
	return (0);
}
