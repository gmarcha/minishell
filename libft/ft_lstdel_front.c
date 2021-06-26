/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:50:54 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/25 15:50:54 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_front(t_list **alst, void (*del)(void*))
{
	t_list			*tmp;

	tmp = *alst;
	*alst = (*alst)->next;
	ft_lstdelone(tmp, del);
}
