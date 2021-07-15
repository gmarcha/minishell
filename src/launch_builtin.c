/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 03:56:42 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/07 03:56:42 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtin(t_cmd *cmd, size_t index_cmd, t_var **env, int exit_status)
{
	int				ret;

	ret = -2;
	if (cmd[0].nb_cmd == 1)
		ret = execute_builtin(cmd, index_cmd, env, exit_status);
	if (ret >= 0)
	{
		if (reset_redirection(cmd, index_cmd) == -1)
		{
			close_cmd_fd(cmd, cmd[0].nb_cmd);
			return (-1);
		}
		close_cmd_fd(cmd, cmd[0].nb_cmd);
	}
	return (ret);
}
