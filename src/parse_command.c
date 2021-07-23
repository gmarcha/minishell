/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 22:00:19 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 22:00:19 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	destroy_command(t_cmd *cmd, size_t nb_cmd, char ***command_redirect)
{
	free_sstrs(command_redirect, nb_cmd);
	free_cmd(cmd, nb_cmd);
	return (-1);
}

static char	*expand_arg(t_cmd *cmd, size_t index_args,
	char ***command_redirect, t_var *env)
{
	char			*expanse;

	expanse = expand_line(command_redirect[cmd[0].index_cmd][index_args],
			env, g_data.exit_status);
	if (expanse == NULL)
		return (NULL);
	free(command_redirect[cmd[0].index_cmd][index_args]);
	command_redirect[cmd[0].index_cmd][index_args] = expanse;
	return (command_redirect[cmd[0].index_cmd][index_args]);
}

static int	parse_arg(t_cmd *cmd, size_t *index_args,
	char ***command_redirect, t_var *env)
{
	size_t			i;

	i = cmd[0].index_cmd;
	if (expand_arg(cmd, *index_args, command_redirect, env) == NULL)
		return (-1);
	if (*command_redirect[i][*index_args] == '\0')
		return (0);
	if (remove_quotes(command_redirect[i] + *index_args) == -1)
		return (-1);
	cmd[i].args = add_arg_to_args(cmd[i].args,
			command_redirect[i][*index_args]);
	if (cmd[i].args == NULL)
		return (-1);
	return (0);
}

static int	parse_args(t_cmd *cmd, size_t *index_args,
	char ***command_redirect, t_var *env)
{
	size_t			i;

	i = cmd[0].index_cmd;
	if (command_redirect[i][*index_args][0] == '<')
	{
		if (parse_infile(cmd, i, index_args, command_redirect) == -1)
			return (-1);
	}
	else if (command_redirect[i][*index_args][0] == '>')
	{
		if (parse_outfile(cmd, i, index_args, command_redirect) == -1)
			return (-1);
	}
	else
	{
		if (parse_arg(cmd, index_args, command_redirect, env) == -1)
			return (-1);
	}
	return (0);
}

int	parse_command(t_cmd *cmd, size_t nb_cmd, char ***command_redirect,
	t_var *env)
{
	size_t			index_args;

	cmd[0].index_cmd = 0;
	while (cmd[0].index_cmd < nb_cmd)
	{
		index_args = 0;
		while (command_redirect[cmd[0].index_cmd][index_args] != NULL)
		{
			if (parse_args(cmd, &index_args, command_redirect, env) == -1)
				return (destroy_command(cmd, nb_cmd, command_redirect));
			index_args++;
		}
		cmd[0].index_cmd++;
	}
	free_sstrs(command_redirect, nb_cmd);
	return (0);
}
