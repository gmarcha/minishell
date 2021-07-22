/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:08:12 by qdam              #+#    #+#             */
/*   Updated: 2021/07/22 16:19:42 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	show_error_cd(char *path, char *msg)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (path)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	return (1);
}

static int	proceed_cd(char *dir, t_var *var_list)
{
	char	*from;
	char	*to;

	from = getcwd(NULL, 0);
	if (chdir(dir))
	{
		free(from);
		return (show_error_cd(dir, strerror(errno)));
	}
	to = getcwd(NULL, 0);
	if (from)
		add_var(&var_list, "OLDPWD", from);
	if (to)
		add_var(&var_list, "PWD", to);
	free(from);
	free(to);
	return (0);
}

int	mini_cd(char **args, t_var *var_list)
{
	char	**home_args;

	if (!args || (args[0] && args[0][0] == 0))
		return (0);
	if (!(*args))
	{
		if (!check_var_exist(var_list, "HOME"))
			return (show_error_cd(NULL, CD_HOME_ERROR));
		home_args = (char *[]){get_var(var_list, "HOME"), NULL};
		return (mini_cd(home_args, var_list));
	}
	if (args[1])
		return (show_error_cd(NULL, CD_ARG_ERROR));
	return (proceed_cd(args[0], var_list));
}
