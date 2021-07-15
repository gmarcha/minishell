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

void	execute(t_cmd *cmd, size_t index_cmd, t_var **env, int exit_status)
{
	char			**envp;
	int				ret;

	close_cmd_fd(cmd, cmd[0].nb_cmd);
	ret = execute_builtin(cmd, index_cmd, env, exit_status);
	if (ret >= 0)
		destroy_process(cmd, cmd[0].nb_cmd, env, ret);
	envp = export_to_envp(*env);
	if (envp == NULL)
		destroy_process(cmd, cmd[0].nb_cmd, env, ret);
	if (execute_path(cmd, index_cmd, *env, envp) == -1)
	{
		ft_free_strs(envp);
		destroy_process(cmd, cmd[0].nb_cmd, env, 1);
	}
	if (execve(cmd[index_cmd].args[0], cmd[index_cmd].args, envp) == -1)
	{
		p_error(cmd[index_cmd].args[0], "command not found", 0);
		ft_free_strs(envp);
		destroy_process(cmd, cmd[0].nb_cmd, env, 127);
	}
}
