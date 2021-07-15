/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:46:04 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 14:46:04 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd, size_t nb_cmd)
{
	size_t			index_cmd;

	index_cmd = 0;
	while (index_cmd < nb_cmd)
	{
		if (cmd[index_cmd].args != NULL)
			ft_free_strs(cmd[index_cmd].args);
		if (cmd[index_cmd].name_in != NULL)
			free(cmd[index_cmd].name_in);
		if (cmd[index_cmd].name_out != NULL)
			free(cmd[index_cmd].name_out);
		index_cmd++;
	}
	free(cmd);
}
