/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_is_line_not_empty.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 17:21:34 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 17:21:34 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	string_is_empty(char *line_expand)
{
	size_t			i;

	i = 0;
	while (line_expand[i] != '\0')
		if (line_expand[i++] != ' ')
			return (0);
	return (1);
}

static int	handling_error_pipeline(char *line_expand)
{
	p_error(PROGRAM_NAME, "syntax error near unexpected token `|'", 0);
	free(line_expand);
	return (-1);
}

static int	is_line_valid(char *line_expand, size_t *status, size_t *pos)
{
	if (line_expand[*pos] == ' ')
		;
	else if (line_expand[*pos] == '|')
	{
		if (*status == 0)
			return (handling_error_pipeline(line_expand));
		*status = 0;
	}
	else
	{
		if (line_expand[*pos] == '\'')
			while (line_expand[--(*pos)] != '\'')
				;
		else if (line_expand[*pos] == '"')
			while (line_expand[--(*pos)] != '"')
				;
		*status = 1;
	}
	return (0);
}

int	is_line_not_empty(char *line_expand)
{
	size_t			pos;
	size_t			status;

	pos = ft_strlen(line_expand);
	if (pos == 0 || string_is_empty(line_expand) == 1)
	{
		free(line_expand);
		return (-1);
	}
	status = 0;
	while (pos-- != 0)
	{
		if (is_line_valid(line_expand, &status, &pos) == -1)
		{
			g_data.exit_status = 2;
			return (-1);
		}
	}
	if (status == 0)
	{
		g_data.exit_status = 2;
		return (handling_error_pipeline(line_expand));
	}
	return (0);
}
