/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 00:55:18 by qdam              #+#    #+#             */
/*   Updated: 2021/07/14 22:54:44 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(char **args, t_var *var_list)
{
	t_var	*var;

	if (var_list)
	{
		(void)args;
		var = var_list;
		while (var)
		{
			ft_putstr_fd(var->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(var->value, STDOUT_FILENO);
			var = var->next;
		}
	}
	return (0);
}
