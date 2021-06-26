/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_wrap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 23:35:51 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/25 23:35:51 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_wrap(t_list **mem_ref, void *content)
{
	t_list			*mem_node;

	if (*mem_ref == NULL)
		return ;
	if (((t_mem_alloc *)(*mem_ref)->content)->content == content)
	{
		ft_lstdel_front(mem_ref, free_mem_alloc);
		return ;
	}
	mem_node = *mem_ref;
	while (mem_node != NULL && mem_node->next != NULL)
	{
		if (((t_mem_alloc *)mem_node->next->content)->content == content)
		{
			ft_lstdel_front(&mem_node->next, free_mem_alloc);
			return ;
		}
		mem_node = mem_node->next;
	}
}
