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

static char	*alloc_removed_quotes(char ***command_redirect,
	size_t index_cmd, size_t index_args)
{
	size_t			size;
	char			*tmp;

	size = ft_strlen(command_redirect[index_cmd][index_args]);
	tmp = (char *)malloc(sizeof(char) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	ft_memset(tmp, 0, size + 1);
	return (tmp);
}

int	remove_quotes(char ***command_redirect, size_t index_cmd, size_t index_args)
{
	size_t			i;
	size_t			j;
	char			*tmp;

	tmp = alloc_removed_quotes(command_redirect, index_cmd, index_args);
	if (tmp == NULL)
		return (-1);
	j = 0;
	i = 0;
	while (command_redirect[index_cmd][index_args][i] != '\0')
	{
		if (command_redirect[index_cmd][index_args][i] == '\'')
			while (command_redirect[index_cmd][index_args][++i] != '\'')
				tmp[j++] = command_redirect[index_cmd][index_args][i];
		else if (command_redirect[index_cmd][index_args][i] == '"')
			while (command_redirect[index_cmd][index_args][++i] != '"')
				tmp[j++] = command_redirect[index_cmd][index_args][i];
		else
			tmp[j++] = command_redirect[index_cmd][index_args][i];
		i++;
	}
	free(command_redirect[index_cmd][index_args]);
	command_redirect[index_cmd][index_args] = tmp;
	return (0);
}
