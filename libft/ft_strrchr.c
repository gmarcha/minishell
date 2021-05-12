/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:21:00 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:21:00 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int				i;

	i = 0;
	while (s[i])
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	while (i--)
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
	return (0);
}
