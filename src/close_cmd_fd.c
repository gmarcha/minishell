/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_cmd_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 03:08:15 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/05 03:08:15 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_cmd_fd(t_cmd *cmd, size_t nb_cmd)
{
	size_t		i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i].fd_in != -1 && cmd[i].fd_in != STDIN_FILENO)
			close(cmd[i].fd_in);
		if (cmd[i].fd_out != -1 && cmd[i].fd_out != STDOUT_FILENO)
			close(cmd[i].fd_out);
		if (cmd[i].save_stdin != -1 && cmd[i].save_stdin != STDIN_FILENO)
			close(cmd[i].save_stdin);
		if (cmd[i].save_stdout != -1 && cmd[i].save_stdout != STDOUT_FILENO)
			close(cmd[i].save_stdout);
		i++;
	}
}
