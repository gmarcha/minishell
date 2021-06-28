/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:10:21 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/23 19:10:21 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_prefix(t_btree *node, void (*apply_f)(void *))
{
	if (node == NULL)
		return ;
	apply_f(node->content);
	btree_apply_prefix(node->left, apply_f);
	btree_apply_prefix(node->right, apply_f);
}
