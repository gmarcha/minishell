/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:17:59 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:17:59 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	if (dest == src)
		return (dest);
	d = dest;
	s = src;
	if (dest < src)
	{
		i = -1;
		while (++i < n)
			*d++ = *s++;
		return (dest);
	}
	else
	{
		while (n--)
			*(d + n) = *(s + n);
		return (dest);
	}
	return (dest);
}
