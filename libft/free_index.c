/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 23:23:01 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/26 23:23:01 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_index(t_list **mem_ref, const char *name)
{
	t_list			*mem_node;

	if (*mem_ref == NULL || name == NULL)
		return ;
	if (((t_mem_alloc *)(*mem_ref)->content)->name != NULL
		&& ft_strcmp(((t_mem_alloc *)(*mem_ref)->content)->name, name) == 0)
	{
		ft_lstdel_front(mem_ref, free_mem_alloc);
		return ;
	}
	mem_node = *mem_ref;
	while (mem_node != NULL && mem_node->next != NULL)
	{
		if (((t_mem_alloc *)mem_node->next->content)->name != NULL
			&& ft_strcmp(
				((t_mem_alloc *)mem_node->next->content)->name, name) == 0)
		{
			ft_lstdel_front(&mem_node->next, free_mem_alloc);
			return ;
		}
		mem_node = mem_node->next;
	}
}
