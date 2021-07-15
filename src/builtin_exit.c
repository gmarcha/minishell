/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:42:59 by qdam              #+#    #+#             */
/*   Updated: 2021/07/14 23:00:16 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnum(char *str)
{
	if (!str || !(*str))
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	show_error_exit(char *wrong_num)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(wrong_num, STDERR_FILENO);
	ft_putendl_fd(EXIT_ARG_ERROR, STDERR_FILENO);
}

int	mini_exit(char **args, t_var **var_list_ptr)
{
	unsigned char	code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!args || !(*args))
		code = 0;
	else if ((args[0][0] == '-' && !ft_isnum(&args[0][1]))
		|| !ft_isnum(args[0]))
	{
		show_error_exit(args[0]);
		code = 255;
	}
	else
		code = (unsigned char)ft_atoi(args[0]);
	clear_list(var_list_ptr);
	return ((int)code);
}
