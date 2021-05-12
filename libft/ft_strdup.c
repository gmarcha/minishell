/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:19:29 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:19:29 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*d;
	int				i;

	i = 0;
	while (s[i])
		i++;
	d = (char *)malloc(i + 1);
	if (d == 0)
		return (0);
	i = -1;
	while (s[++i])
		d[i] = s[i];
	d[i] = 0;
	return (d);
}
