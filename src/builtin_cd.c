/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:08:12 by qdam              #+#    #+#             */
/*   Updated: 2021/07/15 17:32:27 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	show_error_cd(char *path, char *msg)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (1);
}

int	mini_cd(char **args, t_var *var_list)
{
	char	*cwd;
	char	**home_args;

	if (!args)
		return (0);
	if (!(*args))
	{
		home_args = (char *[]){get_var(var_list, "HOME"), NULL};
		if (!ft_strcmp(EMPTY_STR, home_args[0]))
			return (show_error_cd(NULL, CD_HOME_ERROR));
		return (mini_cd(home_args, var_list));
	}
	if (args[1])
		return (show_error_cd(NULL, CD_ARG_ERROR));
	if (chdir(args[0]))
		return (show_error_cd(args[0], CD_DIR_ERROR));
	cwd = getcwd(NULL, 0);
	set_var(var_list, "OLDPWD", get_var(var_list, "PWD"));
	set_var(var_list, "PWD", cwd);
	free(cwd);
	return (0);
}
