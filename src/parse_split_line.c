/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 17:24:16 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 17:24:16 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_line(char *line_expand)
{
	char			**command_list;
	size_t			i;

	i = 0;
	while (line_expand[i] != '\0')
	{
		skip_quotes(line_expand, &i);
		if (line_expand[i] == '|')
			line_expand[i] = '\n';
		i++;
	}
	command_list = ft_split(line_expand, '\n');
	free(line_expand);
	return (command_list);
}
