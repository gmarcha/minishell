/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_reset_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 22:17:34 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/08 22:17:34 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset_redirection(t_cmd *cmd, size_t index_cmd)
{
	if (dup2(cmd[index_cmd].save_stdin, STDIN_FILENO) == -1)
	{
		p_error(PROGRAM_NAME, "dup2()", errno);
		close_cmd_fd(cmd, cmd[0].nb_cmd);
		return (-1);
	}
	if (dup2(cmd[index_cmd].save_stdout, STDOUT_FILENO) == -1)
	{
		p_error(PROGRAM_NAME, "dup2()", errno);
		close_cmd_fd(cmd, cmd[0].nb_cmd);
		return (-1);
	}
	return (0);
}
