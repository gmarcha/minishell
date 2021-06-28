/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 14:12:45 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/26 14:12:45 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*get_index(t_list **mem_ref, const char *name)
{
	t_list			*mem_node;

	if (name == NULL)
		return (NULL);
	mem_node = *mem_ref;
	while (mem_node != NULL)
	{
		if (((t_mem_alloc *)mem_node->content)->name != NULL
			&& ft_strcmp(((t_mem_alloc *)mem_node->content)->name, name) == 0)
			return (((t_mem_alloc *)mem_node->content)->content);
		mem_node = mem_node->next;
	}
	return (NULL);
}
