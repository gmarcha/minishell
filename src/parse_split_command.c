/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:22:08 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 20:22:08 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	***alloc_strss_cmd(char **command_list, size_t nb_cmd)
{
	char			***command_redirect;

	command_redirect = (char ***)malloc(sizeof(char **) * (nb_cmd + 1));
	if (command_redirect == NULL)
	{
		ft_free_strs(command_list);
		return (NULL);
	}
	command_redirect[nb_cmd] = NULL;
	return (command_redirect);
}

static void	transform_command(char *command)
{
	size_t			i;

	i = 0;
	while (command[i] != '\0')
	{
		skip_quotes(command, &i);
		if (command[i] == ' ')
			command[i] = '\n';
		i++;
	}
}

char	***split_command(char **command_list, size_t nb_cmd)
{
	char			***command_redirect;
	size_t			index_cmd;

	if (expand_redirect_op(command_list, nb_cmd) == NULL)
		return (NULL);
	command_redirect = alloc_strss_cmd(command_list, nb_cmd);
	if (command_redirect == NULL)
		return (NULL);
	index_cmd = 0;
	while (index_cmd < nb_cmd)
	{
		transform_command(command_list[index_cmd]);
		command_redirect[index_cmd] = ft_split(command_list[index_cmd], '\n');
		if (command_redirect == NULL)
		{
			free_sstrs(command_redirect, index_cmd);
			ft_free_strs(command_list);
			return (NULL);
		}
		index_cmd++;
	}
	ft_free_strs(command_list);
	return (command_redirect);
}
