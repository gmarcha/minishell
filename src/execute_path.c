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

static void	destroy_path(t_cmd *cmd, size_t nb_cmd, char **envp,
	char **env_path)
{
	p_error(PROGRAM_NAME, "execute_path()", errno);
	ft_free_strs(env_path);
	destroy_process(cmd, nb_cmd, envp, 1);
}

static char	**retrieve_path(t_cmd *cmd, size_t nb_cmd, char **envp)
{
	char	**env_path;

	env_path = ft_split(getenv("PATH"), ':');
	if (env_path == NULL)
	{
		p_error(PROGRAM_NAME, "path not found", 0);
		destroy_process(cmd, nb_cmd, envp, 1);
	}
	return (env_path);
}

static int	ispath(char *dir_name, char *file_name)
{
	DIR				*dir;
	struct dirent	*ent;

	dir = opendir(dir_name);
	if (dir == NULL)
	{
		if (errno == ENOENT)
			return (0);
		return (-1);
	}
	while (1)
	{
		ent = readdir(dir);
		if (ent == NULL)
		{
			if (errno != 0)
				return (closedir(dir) * 0 - 1);
			break ;
		}
		if (ft_strcmp(ent->d_name, file_name) == 0)
			return (closedir(dir) * 0 + 1);
	}
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

void	execute_path(t_cmd *cmd, size_t nb_cmd, size_t index_cmd, char **envp)
{
	char			**env_path;
	int				ret;
	size_t			i;

	env_path = retrieve_path(cmd, nb_cmd, envp);
	i = -1;
	while (env_path[++i] != NULL)
	{
		ret = ispath(env_path[i], cmd[index_cmd].args[0]);
		if (ret == -1)
			destroy_path(cmd, nb_cmd, envp, env_path);
		if (ret == 1)
		{
			env_path[i] = add_directory(env_path + i, cmd[index_cmd].args[0]);
			if (env_path[i] == NULL)
				destroy_path(cmd, nb_cmd, envp, env_path);
			if (execve(env_path[i], cmd[index_cmd].args, envp) == -1)
			{
				p_error(cmd[index_cmd].args[0], "command not found", 0);
				ft_free_strs(env_path);
				destroy_process(cmd, nb_cmd, envp, 127);
			}
		}
	}
	ft_free_strs(env_path);
}
