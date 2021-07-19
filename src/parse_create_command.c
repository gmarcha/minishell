/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_create_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:27:16 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 20:27:16 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_command(size_t nb_cmd, char ***command_redirect)
{
	t_cmd			*cmd;
	size_t			index_cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * nb_cmd);
	if (cmd == NULL)
	{
		free_sstrs(command_redirect, nb_cmd);
		return (NULL);
	}
	index_cmd = -1;
	while (++index_cmd < nb_cmd)
	{
		cmd[index_cmd].args = NULL;
		cmd[index_cmd].redirection = NULL;
		cmd[index_cmd].redirect_op = NULL;
		cmd[index_cmd].fd_in = STDIN_FILENO;
		cmd[index_cmd].fd_out = STDOUT_FILENO;
		cmd[index_cmd].save_stdin = STDIN_FILENO;
		cmd[index_cmd].save_stdout = STDOUT_FILENO;
		cmd[index_cmd].pid_process = 0;
		cmd[index_cmd].exit_status = 0;
	}
	return (cmd);
}
