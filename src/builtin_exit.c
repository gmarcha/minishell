/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 09:42:59 by qdam              #+#    #+#             */
/*   Updated: 2021/08/01 14:43:18 by gamarcha         ###   ########.fr       */
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

static void	show_error_exit(char *wrong_num, char *msg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (wrong_num)
		ft_putstr_fd(wrong_num, STDERR_FILENO);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
}

int	mini_exit(char **args, t_var **var_list_ptr, int exit_status,
	t_bool one_cmd)
{
	unsigned char	code;

	(void)var_list_ptr;
	if (one_cmd)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!args || !(*args))
		code = (unsigned char)exit_status;
	else if ((*args[0] == '-' && ft_isnum(args[0] + 1))
		|| ft_isnum(args[0]))
	{
		if (args[1])
		{
			show_error_exit(NULL, EXIT_MANY_ARGS);
			return (-1);
		}
		code = (unsigned char)ft_atoi(args[0]);
	}
	else
	{
		show_error_exit(args[0], EXIT_ARG_ERROR);
		code = 2;
	}
	return ((int)code);
}
