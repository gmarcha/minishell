/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:18:11 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:18:11 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
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
	{
		if (*s == c)
		{
			*d++ = *s++;
			i++;
			return ((char *)dest + i);
		}
		*d++ = *s++;
	}
	return (0);
}
