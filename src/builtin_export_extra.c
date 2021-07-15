/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:30:13 by qdam              #+#    #+#             */
/*   Updated: 2021/07/14 22:54:42 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_n_var(t_var *first)
{
	t_var	*var;
	size_t	count;

	var = first;
	count = 0;
	while (var)
	{
		var = var->next;
		count++;
	}
	return (count);
}

static void	sort_str_tab(char **tab)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (*tab == NULL)
		return ;
	i = 0;
	while (tab[++i])
	{
		j = i;
		while (j && ft_strcmp(tab[j], tab[j - 1]) < 0)
		{
			tmp = tab[j];
			tab[j] = tab[j - 1];
			tab[j - 1] = tmp;
			j--;
		}
	}
}

static void	declare_x_var(char *var_name, char *var_val)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var_name, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(var_val, STDOUT_FILENO);
	ft_putendl_fd("\"", STDOUT_FILENO);
}

int	export_only(t_var *var_list)
{
	size_t	size;
	int		i;
	char	**var_names;
	t_var	*var;

	size = count_n_var(var_list);
	var_names = malloc(sizeof(char *) * (size + 1));
	if (!var_names)
		return (1);
	var_names[size] = NULL;
	i = 0;
	var = var_list;
	while (var)
	{
		var_names[i++] = var->name;
		var = var->next;
	}
	sort_str_tab(var_names);
	i = -1;
	while (var_names[++i])
		declare_x_var(var_names[i], get_var(var_list, var_names[i]));
	free(var_names);
	return (0);
}
