/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:14:07 by qdam              #+#    #+#             */
/*   Updated: 2021/07/14 22:59:08 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_echo(char **args)
{
	int	first;
	int	i;

	if (*args == NULL)
		first = -1;
	else if (ft_strncmp("-n", args[0], 3))
		first = 0;
	else
		first = 1;
	i = first;
	while (i != -1 && args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[++i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (first != 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
