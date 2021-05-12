/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:18:02 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:18:02 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	if (dest == src)
		return (dest);
	d = dest;
	s = src;
	i = -1;
	while (++i < n)
		*d++ = *s++;
	return (dest);
}
