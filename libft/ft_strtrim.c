/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:20:56 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:20:56 by gamarcha         ###   ########.fr       */
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

static int	is_set(char c, const char *set)
{
	int			i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	int			start;
	int			end;
	int			i;

	start = 0;
	while (s1[start] && is_set(s1[start], set))
		start++;
	end = ft_strsize(s1);
	while (start < end && is_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(end - start + 1);
	if (str == 0)
		return (0);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}
