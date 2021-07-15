/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:23:26 by qdam              #+#    #+#             */
/*   Updated: 2021/07/14 23:00:35 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export_only(t_var *var_list);

static void	show_error_export(char *var_name, t_bool *error_ptr)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(var_name, STDERR_FILENO);
	ft_putendl_fd(ENV_NAME_ERROR, STDERR_FILENO);
	*error_ptr = TRUE;
}

static t_bool
	export_check_arg(char *arg, char **tab, t_var **var_list_ptr)
{
	t_bool	eq;
	t_bool	error;

	eq = (ft_strchr(arg, '=') != NULL);
	error = FALSE;
	if (!check_var_name(tab[0]))
		show_error_export(tab[0], &error);
	else if (eq && ((tab[1] && !add_var(var_list_ptr, tab[0], tab[1]))
			|| (!tab[1] && !add_var(var_list_ptr, tab[0], ""))))
		error = TRUE;
	return (error);
}

int	mini_export(char **args, t_var **var_list_ptr)
{
	int		i;
	t_bool	error;
	char	**tab;

	i = -1;
	error = FALSE;
	while (args[++i])
	{
		if (args[i][0] != '=')
		{
			tab = ft_split(args[i], '=');
			if (!tab)
				return (1);
			if (export_check_arg(args[i], tab, var_list_ptr))
				error = TRUE;
			ft_free_strs(tab);
		}
		else
			show_error_export(args[i], &error);
	}
	if (!i)
		return (export_only(*var_list_ptr));
	return (error == TRUE);
}
