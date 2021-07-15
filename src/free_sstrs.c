/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sstrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 15:33:19 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 15:33:19 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_sstrs(char ***command_redirect, size_t nb_cmd)
{
	size_t			i;

	i = 0;
	while (i < nb_cmd)
		ft_free_strs(command_redirect[i++]);
	free(command_redirect);
}
