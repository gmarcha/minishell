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

static int	parse_infile(t_cmd *cmd, size_t *index_args,
	char ***command_redirect)
{
	cmd[cmd[0].index_cmd].redirect_op = add_arg_to_args(cmd[cmd[0].index_cmd].redirect_op, command_redirect[cmd[0].index_cmd][*index_args]);
	if (cmd[cmd[0].index_cmd].redirect_op == NULL)
		return (-1);
	(*index_args)++;
	if (command_redirect[cmd[0].index_cmd][*index_args] == NULL
		|| ft_ischarset(*command_redirect[cmd[0].index_cmd][*index_args], "<>") == 1)
	{
		if (cmd[cmd[0].index_cmd].redirect_op[ft_strslen((const char **)cmd[cmd[0].index_cmd].redirect_op) - 1][1] == '<')
			p_error(PROGRAM_NAME, "syntax error near unexpected token `<<'", 0);
		else
			p_error(PROGRAM_NAME, "syntax error near unexpected token `<'", 0);
		g_exit_status = 2;
		return (-1);
	}
	cmd[cmd[0].index_cmd].redirection = add_arg_to_args(
			cmd[cmd[0].index_cmd].redirection, command_redirect[cmd[0].index_cmd][*index_args]);
	if (cmd[cmd[0].index_cmd].redirection == NULL)
		return (-1);
	return (0);
}

static int	parse_outfile(t_cmd *cmd, size_t *index_args,
	char ***command_redirect)
{
	cmd[cmd[0].index_cmd].redirect_op = add_arg_to_args(cmd[cmd[0].index_cmd].redirect_op, command_redirect[cmd[0].index_cmd][*index_args]);
	if (cmd[cmd[0].index_cmd].redirect_op == NULL)
		return (-1);
	(*index_args)++;
	if (command_redirect[cmd[0].index_cmd][*index_args] == NULL
		|| ft_ischarset(*command_redirect[cmd[0].index_cmd][*index_args], "<>") == 1)
	{
		if (cmd[cmd[0].index_cmd].redirect_op[ft_strslen((const char **)cmd[cmd[0].index_cmd].redirect_op) - 1][1] == '>')
			p_error(PROGRAM_NAME, "syntax error near unexpected token `>>'", 0);
		else
			p_error(PROGRAM_NAME, "syntax error near unexpected token `>'", 0);
		g_exit_status = 2;
		return (-1);
	}
	cmd[cmd[0].index_cmd].redirection = add_arg_to_args(
			cmd[cmd[0].index_cmd].redirection, command_redirect[cmd[0].index_cmd][*index_args]);
	if (cmd[cmd[0].index_cmd].redirection == NULL)
		return (-1);
	return (0);

}

static char	*expand_arg(t_cmd *cmd, size_t index_args,
	char ***command_redirect, t_var *env)
{
	char			*expanse;

	expanse = expand_line(command_redirect[cmd[0].index_cmd][index_args],
		env, g_exit_status);
	if (expanse == NULL)
		return (NULL);
	free(command_redirect[cmd[0].index_cmd][index_args]);
	command_redirect[cmd[0].index_cmd][index_args] = expanse;
	return (command_redirect[cmd[0].index_cmd][index_args]);
}

static int	parse_arg(t_cmd *cmd, size_t *index_args,
	char ***command_redirect, t_var *env)
{
	if (command_redirect[cmd[0].index_cmd][*index_args][0] == '<')
	{
		if (parse_infile(cmd, index_args, command_redirect) == -1)
			return (-1);
	}
	else if (command_redirect[cmd[0].index_cmd][*index_args][0] == '>')
	{
		if (parse_outfile(cmd, index_args, command_redirect) == -1)
			return (-1);
	}
	else
	{
		if (expand_arg(cmd, *index_args, command_redirect, env) == NULL)
			return (-1);
		if (*command_redirect[cmd[0].index_cmd][*index_args] == '\0')
			return (0);
		if (remove_quotes(command_redirect[cmd[0].index_cmd] + *index_args) == -1)
			return (-1);
		cmd[cmd[0].index_cmd].args = add_arg_to_args(
				cmd[cmd[0].index_cmd].args, command_redirect[cmd[0].index_cmd][*index_args]);
		if (cmd[cmd[0].index_cmd].args == NULL)
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
			if (parse_arg(cmd, &index_args, command_redirect, env) == -1)
				return (destroy_command(cmd, nb_cmd, command_redirect));
			index_args++;
		}
		cmd[0].index_cmd++;
	}
	free_sstrs(command_redirect, nb_cmd);
	return (0);
}
