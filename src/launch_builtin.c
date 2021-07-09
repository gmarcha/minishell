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

int	launch_builtin(t_cmd *cmd, size_t nb_cmd, size_t index_cmd, char **envp)
{
	char			**builtin;
	size_t			i;

	(void)envp;
	builtin = (char *[])
	{"echo", "cd", "pwd", "export", "unset", "env", "exit", 0};
	i = 0;
	while (builtin[i] != NULL)
	{
		if (ft_strcmp(cmd[index_cmd].args[0], builtin[i]) == 0)
		{
			// close some pipes
			cmd[index_cmd].exit_status = 0; // FUNCTION POINTER TO BUILTIN
			if (reset_redirection(cmd, nb_cmd, index_cmd) == -1)
				return (-1);
			return (cmd[index_cmd].exit_status);
		}
		i++;
	}
	return (-2);
}
