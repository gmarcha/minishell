/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 22:58:03 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/05 22:58:03 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strconcat(char **str, char *new)
{
	char			*tmp;

	if (*str == NULL)
	{
		*str = ft_strdup("");
		if (*str == NULL)
			return (NULL);
	}
	tmp = ft_strjoin(*str, new);
	free(*str);
	*str = tmp;
	return (*str);
}
