/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 23:35:55 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/25 23:35:55 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	malloc_destroy(t_list **global_ref, t_list **local_ref)
{
	if (local_ref != NULL)
		malloc_clear(local_ref);
	malloc_clear(global_ref);
	exit(1);
}
