/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:14:47 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:14:47 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*str;
	void			*s;
	size_t			i;

	s = malloc(nmemb * size);
	if (s == 0)
		return (0);
	str = s;
	i = 0;
	while (i < nmemb * size)
		str[i++] = 0;
	return (s);
}
