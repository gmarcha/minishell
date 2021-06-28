/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 22:34:31 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/23 22:34:31 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*btree_search_data(
	t_btree *node, void *data_ref, int (*cmp_f)(void *, void *))
{
	if (node == NULL)
		return (NULL);
	if (btree_search_data(node->left, data_ref, cmp_f) != NULL)
		return (data_ref);
	if (cmp_f(node->content, data_ref) == 0)
		return (data_ref);
	return (btree_search_data(node->right, data_ref, cmp_f));
}
