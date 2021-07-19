/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 17:20:10 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 17:20:10 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*expand_single_quote(char **line_ptr)
{
	size_t	i;
	char	*s;
	t_node	*node;

	i = 1;
	while ((*line_ptr)[i] && (*line_ptr)[i] != '\'')
		i++;
	if ((*line_ptr)[i] == '\'')
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	ft_strlcpy(s, *line_ptr, i + 1);
	(*line_ptr) += i;
	node = new_node(0, s, TRUE);
	if (!node)
		free(s);
	return (node);
}

static t_node	*expand_dollar(char **line_ptr, t_var *var_list, int exit_code,
	t_bool in_quote)
{
	char	var_name[1024];
	size_t	i;
	t_node	*node;

	(*line_ptr)++;
	if (**line_ptr == '?')
	{
		node = new_node(0, ft_itoa(exit_code), TRUE);
		(*line_ptr)++;
		if (node && !node->s)
			return (clear_nodes(node));
		return (node);
	}
	i = 0;
	while ((*line_ptr)[i] == '_' || ft_isalnum((*line_ptr)[i]))
		i++;
	ft_strlcpy(var_name, *line_ptr, i + 1);
	if (!check_var_name(var_name))
		return (new_node('$', NULL, FALSE));
	(*line_ptr) += i;
	if (in_quote)
		return (new_node(0, get_var(var_list, var_name), FALSE));
	return (new_node(0, trim_spaces(get_var(var_list, var_name)), TRUE));
}

static t_node	*expand_char(char **line_ptr)
{
	t_node	*node;

	node = new_node(**line_ptr, NULL, FALSE);
	(*line_ptr)++;
	return (node);
}

char	*expand_line(char *line_content, t_var *env, int exit_status)
{
	t_bool	in_quote;
	t_node	*start;
	t_node	*cur;

	if (*line_content == '\0')
		return (ft_strdup(""));
	in_quote = FALSE;
	start = NULL;
	while (*line_content)
	{
		if (!in_quote && *line_content == '\'')
			cur = expand_single_quote(&line_content);
		else if (*line_content == '$')
			cur = expand_dollar(&line_content, env, exit_status, in_quote);
		else
		{
			if (*line_content == '"')
				in_quote = !in_quote;
			cur = expand_char(&line_content);
		}
		if (!cur)
			return (clear_nodes(start));
		append_node(&start, cur);
	}
	return (join_nodes(start));
}
