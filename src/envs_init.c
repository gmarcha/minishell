/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdam <qdam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:30:11 by qdam              #+#    #+#             */
/*   Updated: 2021/07/11 20:19:17 by qdam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_var_name(char *name)
{
	size_t	i;

	if (!name || (!ft_isalpha(*name) && *name != '_'))
		return (FALSE);
	i = 0;
	while (name[++i])
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (FALSE);
	return (TRUE);
}

t_var	*make_var(char *name, char *value)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	var->next = NULL;
	if (!var->name || !var->value)
	{
		destroy_var(var);
		var = NULL;
	}
	return (var);
}

t_var	*construct_globals(char **envp)
{
	t_var	*globals;
	t_var	*var;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	globals = NULL;
	while (i--)
	{
		*(ft_strchr(envp[i], '=')) = 0;
		var = make_var(envp[i], ft_strchr(envp[i], 0) + 1);
		*(ft_strchr(envp[i], 0)) = '=';
		if (!var)
		{
			clear_list(&globals);
			break ;
		}
		var->next = globals;
		globals = var;
	}
	return (globals);
}
