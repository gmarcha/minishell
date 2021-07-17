/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_remove_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:40:51 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 20:40:51 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*alloc_removed_quotes(char *command)
{
	size_t			size;
	char			*tmp;

	size = ft_strlen(command);
	tmp = (char *)malloc(sizeof(char) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	ft_memset(tmp, 0, size + 1);
	return (tmp);
}

int	remove_quotes(char **command)
{
	size_t			i;
	size_t			j;
	char			*tmp;

	tmp = alloc_removed_quotes(*command);
	if (tmp == NULL)
		return (-1);
	j = 0;
	i = 0;
	while ((*command)[i] != '\0')
	{
		if ((*command)[i] == '\'')
			while ((*command)[++i] != '\'')
				tmp[j++] = (*command)[i];
		else if ((*command)[i] == '"')
			while ((*command)[++i] != '"')
				tmp[j++] = (*command)[i];
		else
			tmp[j++] = (*command)[i];
		i++;
	}
	free(*command);
	*command = tmp;
	return (0);
}
