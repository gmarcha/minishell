/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 21:19:14 by gamarcha          #+#    #+#             */
/*   Updated: 2021/04/15 21:19:14 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_strs(char **strs, int size)
{
	int				i;

	i = 0;
	while (i < size)
		free(strs[i++]);
	free(strs);
	return (0);
}

static int	get_nbr_words(const char *str, char sep)
{
	int				count;
	int				i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

static char	*allocate_string(char const *s, char c)
{
	char			*str;
	int				j;

	j = 0;
	while (s[j] && s[j] != c)
		j++;
	str = (char *)malloc(j + 1);
	if (str == 0)
		return (0);
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char			**strs;
	int				len;
	int				i;
	int				j;

	len = get_nbr_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (len + 1));
	if (strs == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		while (*s && *s == c)
			s++;
		strs[i] = allocate_string(s, c);
		if (strs[i] == 0)
			return (free_strs(strs, i));
		j = 0;
		while (*s && *s != c)
			strs[i][j++] = *s++;
		strs[i++][j] = 0;
	}
	strs[i] = 0;
	return (strs);
}
