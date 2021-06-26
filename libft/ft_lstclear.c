/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:16:58 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:16:58 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list			*tmp;
	t_list			*node;

	node = *lst;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		ft_lstdelone(tmp, del);
	}
	*lst = 0;
}
