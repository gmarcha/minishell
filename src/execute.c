/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 02:53:36 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/05 02:53:36 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cmd *cmd, size_t nb_cmd, size_t index_cmd, char **envp)
{
	close_cmd_fd(cmd, nb_cmd);
	execute_path(cmd, nb_cmd, index_cmd, envp);
	if (execve(cmd[index_cmd].args[0], cmd[index_cmd].args, envp) == -1)
	{
		p_error(cmd[index_cmd].args[0], "command not found", 0);
		destroy_process(cmd, nb_cmd, envp, 127);
	}
}
