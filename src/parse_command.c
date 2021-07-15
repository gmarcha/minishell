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

static int	parse_infile(t_cmd *cmd, size_t index_cmd, size_t *index_args,
	char ***command_redirect)
{
	if (command_redirect[index_cmd][*index_args][1] == '<')
		cmd[index_cmd].redirect_in = DOUBLE_REDIRECTION;
	else
		cmd[index_cmd].redirect_in = SIMPLE_REDIRECTION;
	(*index_args)++;
	if (command_redirect[index_cmd][*index_args] == NULL
		|| ft_ischarset(*command_redirect[index_cmd][*index_args], "<>") == 1)
	{
		if (cmd[index_cmd].redirect_in == DOUBLE_REDIRECTION)
			p_error(PROGRAM_NAME, "syntax error near unexpected token `<<'", 0);
		else
			p_error(PROGRAM_NAME, "syntax error near unexpected token `<'", 0);
		return (-1);
	}
	if (remove_quotes(command_redirect, index_cmd, *index_args) == -1)
		return (-1);
	if (cmd[index_cmd].name_in != NULL)
		free(cmd[index_cmd].name_in);
	cmd[index_cmd].name_in = ft_strdup(
			command_redirect[index_cmd][*index_args]);
	if (cmd[index_cmd].name_in == NULL)
		return (-1);
	return (0);
}

static int	parse_outfile(t_cmd *cmd, size_t index_cmd, size_t *index_args,
	char ***command_redirect)
{
	if (command_redirect[index_cmd][*index_args][1] == '>')
		cmd[index_cmd].redirect_out = DOUBLE_REDIRECTION;
	else
		cmd[index_cmd].redirect_out = SIMPLE_REDIRECTION;
	(*index_args)++;
	if (command_redirect[index_cmd][*index_args] == NULL
		|| ft_ischarset(*command_redirect[index_cmd][*index_args], "<>") == 1)
	{
		if (cmd[index_cmd].redirect_out == DOUBLE_REDIRECTION)
			p_error(PROGRAM_NAME, "syntax error near unexpected token `>>'", 0);
		else
			p_error(PROGRAM_NAME, "syntax error near unexpected token `>'", 0);
		return (-1);
	}
	if (remove_quotes(command_redirect, index_cmd, *index_args) == -1)
		return (-1);
	if (cmd[index_cmd].name_out != NULL)
		free(cmd[index_cmd].name_out);
	cmd[index_cmd].name_out = ft_strdup(
			command_redirect[index_cmd][*index_args]);
	if (cmd[index_cmd].name_out == NULL)
		return (-1);
	return (0);
}

static int	parse_arg(t_cmd *cmd, size_t index_cmd, size_t *index_args,
	char ***command_redirect)
{
	if (command_redirect[index_cmd][*index_args][0] == '<')
	{
		if (parse_infile(cmd, index_cmd, index_args, command_redirect) == -1)
			return (-1);
	}
	else if (command_redirect[index_cmd][*index_args][0] == '>')
	{
		if (parse_outfile(cmd, index_cmd, index_args, command_redirect) == -1)
			return (-1);
	}
	else
	{
		if (remove_quotes(command_redirect, index_cmd, *index_args) == -1)
			return (-1);
		cmd[index_cmd].args = add_arg_to_args(
				cmd[index_cmd].args, command_redirect[index_cmd][*index_args]);
		if (cmd[index_cmd].args == NULL)
			return (-1);
	}
	return (0);
}

int	parse_command(t_cmd *cmd, size_t nb_cmd, char ***command_redirect)
{
	size_t			index_cmd;
	size_t			index_args;

	index_cmd = 0;
	while (index_cmd < nb_cmd)
	{
		index_args = 0;
		while (command_redirect[index_cmd][index_args] != NULL)
		{
			if (parse_arg(cmd, index_cmd, &index_args, command_redirect) == -1)
				return (destroy_command(cmd, nb_cmd, command_redirect));
			index_args++;
		}
		index_cmd++;
	}
	free_sstrs(command_redirect, nb_cmd);
	return (0);
}
