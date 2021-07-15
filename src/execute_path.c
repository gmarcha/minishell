/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 03:55:00 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/07 03:55:00 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	destroy_path(char **env_path)
{
	p_error(PROGRAM_NAME, "execute_path()", errno);
	ft_free_strs(env_path);
	return (-1);
}

static char	**retrieve_path(t_var *env)
{
	char	*path;

	path = get_var(env, "PATH");
	if (*path == '\0')
	{
		p_error(PROGRAM_NAME, "path not found in environment", 0);
		return (NULL);
	}
	return (ft_split(path, ':'));
}

static int	ispath(char *dir_name, char *file_name)
{
	DIR				*dir;
	struct dirent	*ent;

	dir = opendir(dir_name);
	if (dir == NULL)
	{
		if (errno == ENOENT || errno == EACCES || errno == ENOTDIR)
			return (0);
		return (-1);
	}
	errno = 0;
	ent = readdir(dir);
	while (ent != NULL)
	{
		if (ft_strcmp(ent->d_name, file_name) == 0)
			return (closedir(dir) * 0 + 1);
		errno = 0;
		ent = readdir(dir);
	}
	if (errno != 0)
		return (closedir(dir) * 0 - 1);
	return (closedir(dir) * 0);
}

static char	*add_directory(char **env_path, char *name_exec)
{
	*env_path = ft_strconcat(env_path, "/");
	if (*env_path == NULL)
		return (NULL);
	*env_path = ft_strconcat(env_path, name_exec);
	if (*env_path == NULL)
		return (NULL);
	return (*env_path);
}

int	execute_path(t_cmd *cmd, size_t index_cmd, t_var *env, char **envp)
{
	char			**env_path;
	int				ret;
	size_t			i;

	env_path = retrieve_path(env);
	if (env_path == NULL)
		return (-1);
	i = -1;
	while (env_path[++i] != NULL)
	{
		ret = ispath(env_path[i], cmd[index_cmd].args[0]);
		if (ret == -1)
			return (destroy_path(env_path));
		if (ret == 1)
		{
			env_path[i] = add_directory(env_path + i, cmd[index_cmd].args[0]);
			if (env_path[i] == NULL)
				return (destroy_path(env_path));
			if (execve(env_path[i], cmd[index_cmd].args, envp) == -1)
				return (destroy_path(env_path));
		}
	}
	ft_free_strs(env_path);
	return (0);
}
