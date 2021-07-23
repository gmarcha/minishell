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

static void	print_sigquit(t_cmd *cmd, size_t nb_cmd)
{
	size_t			k;

	if (cmd[nb_cmd - 1].exit_status == 131)
		write(1, "^\\Quit\n", 7);
	else
	{
		k = 0;
		while (k < nb_cmd - 1)
		{
			if (cmd[k].exit_status == 131)
			{
				write(1, "^\\", 2);
				break ;
			}
			k++;
		}
	}
}

int	wait_process(t_cmd *cmd, size_t nb_cmd)
{
	int				status;
	pid_t			pid_exec;
	size_t			k;

	pid_exec = wait(&status);
	while (pid_exec != -1)
	{
		k = 0;
		while (cmd[k].pid_process != pid_exec)
			k++;
		if (WIFEXITED(status))
			cmd[k].exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cmd[k].exit_status = WTERMSIG(status) + 128;
		pid_exec = wait(&status);
	}
	print_sigquit(cmd, nb_cmd);
	g_data.is_execution = 0;
	return (cmd[nb_cmd - 1].exit_status);
}
