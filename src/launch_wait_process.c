/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_wait_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 04:02:08 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/07 04:02:08 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_process(t_cmd *cmd, size_t nb_cmd)
{
	int				status;
	pid_t			pid_exec;
	size_t			i;
	size_t			k;

	i = 0;
	while (i++ < nb_cmd)
	{
		pid_exec = wait(&status);
		if (pid_exec == -1)
		{
			p_error(PROGRAM_NAME, "wait()", errno);
			return (1);
		}
		k = 0;
		while (cmd[k].pid_process != pid_exec)
			k++;
		if (WIFEXITED(status))
			cmd[k].exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cmd[k].exit_status = WTERMSIG(status);
	}
	return (cmd[nb_cmd - 1].exit_status);
}
