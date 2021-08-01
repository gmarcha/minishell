/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:50:42 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 11:50:42 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	destroy_program(t_cmd *cmd, size_t index_cmd, t_var **env,
	int exit_status)
{
	int				status;

	status = mini_exit(cmd[index_cmd].args + 1, env, exit_status,
			(cmd[0].nb_cmd == 1));
	if (status > -1)
	{
		free_cmd(cmd, cmd[0].nb_cmd);
		clear_list(env);
		exit(status);
	}
	return (1);
}

int	execute_builtin(t_cmd *cmd, size_t index_cmd, t_var **env, int exit_status)
{
	if (cmd[index_cmd].args == NULL)
		return (-2);
	if (ft_strcmp(cmd[index_cmd].args[0], "cd") == 0)
		return (mini_cd(cmd[index_cmd].args + 1, *env));
	if (ft_strcmp(cmd[index_cmd].args[0], "echo") == 0)
		return (mini_echo(cmd[index_cmd].args + 1));
	if (ft_strcmp(cmd[index_cmd].args[0], "env") == 0)
		return (mini_env(cmd[index_cmd].args + 1, *env));
	if (ft_strcmp(cmd[index_cmd].args[0], "exit") == 0)
		return (destroy_program(cmd, index_cmd, env, exit_status));
	if (ft_strcmp(cmd[index_cmd].args[0], "export") == 0)
		return (mini_export(cmd[index_cmd].args + 1, env));
	if (ft_strcmp(cmd[index_cmd].args[0], "pwd") == 0)
		return (mini_pwd(cmd[index_cmd].args + 1, *env));
	if (ft_strcmp(cmd[index_cmd].args[0], "unset") == 0)
		return (mini_unset(cmd[index_cmd].args + 1, env));
	return (-2);
}
