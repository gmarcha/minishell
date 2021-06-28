/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:18:31 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/23 19:18:31 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_infix(t_btree *node, void (*apply_f)(void *))
{
	if (node == NULL)
		return ;
	btree_apply_infix(node->left, apply_f);
	apply_f(node->content);
	btree_apply_infix(node->right, apply_f);
}
