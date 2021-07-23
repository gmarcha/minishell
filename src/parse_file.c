/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 17:59:20 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/19 17:59:20 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_infile(t_cmd *cmd, size_t i, size_t *index_args,
	char ***command_redirect)
{
	cmd[i].redirect_op = add_arg_to_args(
			cmd[i].redirect_op, command_redirect[i][*index_args]);
	if (cmd[i].redirect_op == NULL)
		return (-1);
	(*index_args)++;
	if (command_redirect[i][*index_args] == NULL
		|| ft_ischarset(*command_redirect[i][*index_args], "<>") == 1)
	{
		if (cmd[i].redirect_op
			[ft_strslen((const char **)cmd[i].redirect_op) - 1][1] == '<')
			p_error(PROGRAM_NAME, "syntax error near unexpected token `<<'", 0);
		else
			p_error(PROGRAM_NAME, "syntax error near unexpected token `<'", 0);
		g_data.exit_status = 2;
		return (-1);
	}
	cmd[i].redirection = add_arg_to_args(
			cmd[i].redirection, command_redirect[i][*index_args]);
	if (cmd[i].redirection == NULL)
		return (-1);
	return (0);
}

int	parse_outfile(t_cmd *cmd, size_t i, size_t *index_args,
	char ***command_redirect)
{
	cmd[i].redirect_op = add_arg_to_args(
			cmd[i].redirect_op, command_redirect[i][*index_args]);
	if (cmd[i].redirect_op == NULL)
		return (-1);
	(*index_args)++;
	if (command_redirect[i][*index_args] == NULL
		|| ft_ischarset(*command_redirect[i][*index_args], "<>") == 1)
	{
		if (cmd[i].redirect_op
			[ft_strslen((const char **)cmd[i].redirect_op) - 1][1] == '>')
			p_error(PROGRAM_NAME, "syntax error near unexpected token `>>'", 0);
		else
			p_error(PROGRAM_NAME, "syntax error near unexpected token `>'", 0);
		g_data.exit_status = 2;
		return (-1);
	}
	cmd[i].redirection = add_arg_to_args(
			cmd[i].redirection, command_redirect[i][*index_args]);
	if (cmd[i].redirection == NULL)
		return (-1);
	return (0);
}
