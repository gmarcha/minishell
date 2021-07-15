/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:23:19 by qdam              #+#    #+#             */
/*   Updated: 2021/07/14 23:02:12 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_error_unset(char *var_name, t_bool *error_ptr)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(var_name, STDERR_FILENO);
	ft_putendl_fd(ENV_NAME_ERROR, STDERR_FILENO);
	*error_ptr = TRUE;
}

int	mini_unset(char **args, t_var **var_list_ptr)
{
	int		i;
	t_bool	error;

	i = -1;
	error = FALSE;
	while (args[++i])
	{
		if (!check_var_name(args[i]))
			show_error_unset(args[i], &error);
		else
			del_var(var_list_ptr, args[i]);
	}
	return (error);
}
