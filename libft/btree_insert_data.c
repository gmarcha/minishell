/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 21:22:39 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/23 21:22:39 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_insert_data(t_btree **node,
			void *content, int (*cmp_f)(void *, void *))
{
	if (*node == NULL)
	{
		*node = btree_create_node(content);
		if (*node == NULL)
			return (NULL);
		return (*node);
	}
	if (cmp_f(content, (*node)->content) < 0)
		return (btree_insert_data(&(*node)->left, content, cmp_f));
	else
		return (btree_insert_data(&(*node)->right, content, cmp_f));
}
