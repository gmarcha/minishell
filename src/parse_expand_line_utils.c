/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:41:28 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/19 16:55:43 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_spaces(char *str)
{
	size_t	i;
	char	*trimmed;

	if (!str)
		return (NULL);
	while (*str == ' ')
		str++;
	i = ft_strlen(str);
	if (i == 0)
		return (ft_strdup(""));
	while (str[i - 1] == ' ')
		i--;
	trimmed = malloc(sizeof(char) * (i + 1));
	if (trimmed)
		ft_strlcpy(trimmed, str, i + 1);
	return (trimmed);
}

t_node	*new_node(char c, char *s, t_bool free_s)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node)
	{
		node->c[0] = c;
		node->c[1] = 0;
		node->s = s;
		if (c)
			node->len = 1;
		else
			node->len = ft_strlen(s);
		node->free_s = free_s;
		node->next = NULL;
	}
	return (node);
}

void	*clear_nodes(t_node *start)
{
	t_node	*cur;
	t_node	*tmp;

	cur = start;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		if (tmp->s && tmp->free_s)
			free(tmp->s);
		free(tmp);
	}
	return (NULL);
}

void	append_node(t_node **start_ptr, t_node *node)
{
	t_node	*cur;

	if (*start_ptr == NULL)
	{
		*start_ptr = node;
		return ;
	}
	cur = *start_ptr;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}

char	*join_nodes(t_node *start)
{
	t_node	*node;
	size_t	len;
	char	*expanded;

	node = start;
	len = 0;
	while (node)
	{
		len += node->len;
		node = node->next;
	}
	node = start;
	expanded = malloc(sizeof(char) * (len + 1));
	len = 0;
	while (expanded && node)
	{
		if (node->c[0])
			ft_strlcpy(&expanded[len], node->c, 2);
		else
			ft_strlcpy(&expanded[len], node->s, ft_strlen(node->s) + 1);
		len += node->len;
		node = node->next;
	}
	clear_nodes(start);
	return (expanded);
}
