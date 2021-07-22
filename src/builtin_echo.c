/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:14:07 by qdam              #+#    #+#             */
/*   Updated: 2021/07/22 16:19:30 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_option_n(char *arg)
{
	if (ft_strlen(arg) < 2)
		return (FALSE);
	if (*(arg++) != '-')
		return (FALSE);
	while (*arg)
		if (*(arg++) != 'n')
			return (FALSE);
	return (TRUE);
}

int	mini_echo(char **args)
{
	t_bool	no_nl;

	no_nl = FALSE;
	if (args && *args)
	{
		while (is_option_n(*args))
		{
			no_nl = TRUE;
			args++;
		}
		while (*args)
		{
			ft_putstr_fd(*args, STDOUT_FILENO);
			if (*(++args))
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (no_nl == FALSE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
