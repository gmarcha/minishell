/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 04:00:39 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/07 04:00:39 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_process(t_cmd *cmd, size_t nb_cmd, char **envp, int exit_status)
{
	(void)envp;
	// ft_free_strs(envp);
	(void)cmd; (void)nb_cmd;
	// free_cmd(cmd, nb_cmd);
	exit(exit_status);
}
