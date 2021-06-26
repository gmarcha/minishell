/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 23:35:48 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/25 23:35:48 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_mem_alloc(void *mem_alloc)
{
	if (((t_mem_alloc *)mem_alloc)->content_free == ft_lstclear)
		((t_mem_alloc *)mem_alloc)->content_free(
			((t_mem_alloc *)mem_alloc)->content, free);
	else
		((t_mem_alloc *)mem_alloc)->content_free(
			((t_mem_alloc *)mem_alloc)->content);
	free(mem_alloc);
}
