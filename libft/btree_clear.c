/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:17:14 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/28 15:20:39 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_clear(t_btree *node, void (*del)(void *))
{
	if (node == NULL)
		return ;
	btree_clear(node->left, del);
	btree_clear(node->right, del);
	if (del != NULL)
		del(node->content);
	free(node);
}
