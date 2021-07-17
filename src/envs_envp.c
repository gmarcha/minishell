/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdam <qdam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:42:51 by qdam              #+#    #+#             */
/*   Updated: 2021/07/11 22:58:31 by qdam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_var_exist(t_var *list, char *name)
{
	t_var	*cur;

	if (!name)
		return (FALSE);
	cur = list;
	while (cur)
	{
		if (!ft_strcmp(cur->name, name))
			return (TRUE);
		cur = cur->next;
	}
	return (FALSE);
}

static t_bool	alloc_single_ev(char **envp, int i, t_var *var)
{
	size_t	len_name;
	size_t	len_val;

	len_name = ft_strlen(var->name);
	len_val = ft_strlen(var->value);
	envp[i] = malloc(sizeof(char) * (len_name + len_val + 2));
	if (!envp[i])
		return (FALSE);
	ft_strlcpy(envp[i], var->name, len_name + 1);
	envp[i][len_name] = '=';
	ft_strlcpy(envp[i] + len_name + 1, var->value, len_val + 1);
	return (TRUE);
}

char	**export_to_envp(t_var *globals)
{
	int		i;
	int		count;
	t_var	*var;
	char	**envp;

	count = -1;
	var = globals;
	while ((++count >= 0) && var)
		var = var->next;
	envp = ft_calloc(count + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = -1;
	var = globals;
	while (++i < count)
	{
		if (!alloc_single_ev(envp, i, var))
		{
			ft_free_strs(envp);
			return (NULL);
		}
		var = var->next;
	}
	return (envp);
}
