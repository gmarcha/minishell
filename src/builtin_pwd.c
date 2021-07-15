/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:51:29 by qdam              #+#    #+#             */
/*   Updated: 2021/07/14 23:01:42 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(char **args, t_var *var_list)
{
	char	*pwd;

	(void)args;
	pwd = get_var(var_list, "PWD");
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (0);
}
