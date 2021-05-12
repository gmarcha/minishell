/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:19:42 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:19:42 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strsize(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			src_len;
	size_t			dst_len;
	size_t			i;

	src_len = ft_strsize(src);
	dst_len = ft_strsize(dst);
	if (size)
	{
		i = 0;
		while (src[i] && i + dst_len + 1 < size)
		{
			dst[i + dst_len] = src[i];
			i++;
		}
		dst[i + dst_len] = 0;
	}
	if (size <= dst_len)
		return (src_len + size);
	else
		return (src_len + dst_len);
}
