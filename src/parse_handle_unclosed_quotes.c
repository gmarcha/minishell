/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handle_unclosed_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 17:17:47 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 17:17:47 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	is_unclose_quote(char *line, size_t *i, char type)
{
	while (line[*i] != '\0')
	{
		if (line[*i] == type)
			return (0);
		(*i)++;
	}
	return (1);
}

static char	*clean_line(char **line, size_t pos, int flag)
{
	char	*clean_line;

	if (flag != 0)
		clean_line = ft_substr(*line, 0, pos);
	else
		clean_line = ft_strdup(*line);
	free(*line);
	*line = NULL;
	return (clean_line);
}

char	*handle_unclosed_quotes(char **line)
{
	size_t			pos;
	size_t			i;

	pos = ft_strlen(*line);
	i = 0;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '\'')
		{
			pos = i++;
			if (is_unclose_quote(*line, &i, '\'') == 1)
				return (clean_line(line, pos, 1));
		}
		else if ((*line)[i] == '"')
		{
			pos = i++;
			if (is_unclose_quote(*line, &i, '"') == 1)
				return (clean_line(line, pos, 1));
		}
		i++;
	}
	return (clean_line(line, 0, 0));
}
