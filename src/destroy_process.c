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

void	destroy_process(t_cmd *cmd, size_t nb_cmd, t_var **env, int exit_status)
{
	free_cmd(cmd, nb_cmd);
	clear_list(env);
	exit(exit_status);
}
