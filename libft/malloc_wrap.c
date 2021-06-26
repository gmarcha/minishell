/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_wrap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 23:36:01 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/25 23:36:01 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*malloc_wrap(
			t_list **mem_ref,
			const char *name, void (*mem_free)(void *), size_t size)
{
	t_mem_alloc		*mem_alloc;
	t_list			*mem_node;

	mem_alloc = (t_mem_alloc *)malloc(sizeof(*mem_alloc));
	if (mem_alloc == NULL)
		return (NULL);
	mem_alloc->content = malloc(size);
	if (mem_alloc->content == NULL)
	{
		free(mem_alloc);
		return (NULL);
	}
	mem_alloc->content_free = mem_free;
	mem_alloc->name = name;
	mem_node = ft_lstnew(mem_alloc);
	if (mem_node == NULL)
	{
		free_mem_alloc(mem_alloc);
		return (NULL);
	}
	ft_lstadd_front(mem_ref, mem_node);
	return (mem_alloc->content);
}
