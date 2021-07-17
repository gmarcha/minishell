/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdam <qdam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:30:59 by qdam              #+#    #+#             */
/*   Updated: 2021/07/13 12:02:42 by qdam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	trim_spaces(char **str)
{
	size_t	i;

	while (**str == ' ')
		(*str)++;
	i = ft_strlen(*str) - 1;
	while ((*str)[i] == ' ')
		i--;
	(*str)[i + 1] = 0;
}

t_bool	add_var(t_var **list, char *name, char *value)
{
	t_var	*new_var;
	t_var	*var;

	if (!list)
		return (FALSE);
	if (check_var_exist(*list, name))
		return (set_var(*list, name, value));
	trim_spaces(&value);
	new_var = make_var(name, value);
	if (!new_var)
		return (FALSE);
	if (!(*list))
		*list = new_var;
	else
	{
		var = *list;
		while (var->next)
			var = var->next;
		var->next = new_var;
	}
	return (TRUE);
}

void	del_var(t_var **list, char *name)
{
	t_var	*to_del;
	t_var	*var;

	if (!list || !(*list) || !name)
		return ;
	to_del = *list;
	while (to_del)
	{
		if (!ft_strcmp(to_del->name, name))
			break ;
		to_del = to_del->next;
	}
	if (!to_del)
		return ;
	if (to_del == *list)
		*list = to_del->next;
	else
	{
		var = *list;
		while (var->next != to_del)
			var = var->next;
		var->next = to_del->next;
	}
	destroy_var(to_del);
}

char	*get_var(t_var *list, char *name)
{
	t_var	*var;

	if (!list || !name || !check_var_name(name))
		return (EMPTY_STR);
	var = list;
	while (var)
	{
		if (!ft_strcmp(var->name, name))
			return (var->value);
		var = var->next;
	}
	return (EMPTY_STR);
}

t_bool	set_var(t_var *list, char *name, char *new_value)
{
	t_var	*var;
	char	*old_value;

	if (!list)
		return (FALSE);
	var = list;
	while (var)
	{
		if (!ft_strcmp(var->name, name))
			break ;
		var = var->next;
	}
	if (!var)
		return (FALSE);
	old_value = var->value;
	if (!ft_strcmp(old_value, new_value))
		return (TRUE);
	var->value = ft_strdup(new_value);
	if (!var->value)
	{
		var->value = old_value;
		return (FALSE);
	}
	free(old_value);
	return (TRUE);
}
