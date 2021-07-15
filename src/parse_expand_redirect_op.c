/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_redirect_op.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:07:44 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 20:07:44 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	copy_size(char **command_list, size_t index_cmd)
{
	size_t			size;
	size_t			i;

	size = 0;
	i = 0;
	while (command_list[index_cmd][i] != '\0')
	{
		skip_quotes(command_list[index_cmd], &i);
		if (command_list[index_cmd][i] == '<')
		{
			if (command_list[index_cmd][i + 1] == '<')
				i++;
			size += 2;
		}
		else if (command_list[index_cmd][i] == '>')
		{
			if (command_list[index_cmd][i + 1] == '>')
				i++;
			size += 2;
		}
		i++;
	}
	return (size + i);
}

static void	copy_quotes(char *command, char *tmp, size_t *i, char *type)
{
	size_t			size;

	size = ft_strclen(command + *i + 1, type) + 2;
	ft_strlcat(tmp, command + *i, ft_strlen(tmp) + size + 1);
	*i += size;
}

static void	copy_redirect_op(char *command, char *tmp, size_t *i, char op)
{
	ft_strlcat(tmp, " ", ft_strlen(tmp) + 2);
	ft_strlcat(tmp, command + *i, ft_strlen(tmp) + 2);
	if (command[(*i)++ + 1] == op)
		ft_strlcat(tmp, command + (*i)++, ft_strlen(tmp) + 2);
	ft_strlcat(tmp, " ", ft_strlen(tmp) + 2);
}

static void	copy_command(char *command, char *tmp)
{
	size_t			i;

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '\'')
			copy_quotes(command, tmp, &i, "'");
		else if (command[i] == '"')
			copy_quotes(command, tmp, &i, "\"");
		else if (command[i] == '<')
			copy_redirect_op(command, tmp, &i, '<');
		else if (command[i] == '>')
			copy_redirect_op(command, tmp, &i, '>');
		else
			ft_strlcat(tmp, command + i++, ft_strlen(tmp) + 2);
	}
}

char	**expand_redirect_op(char **command_list, size_t nb_cmd)
{
	char			*tmp;
	size_t			index_cmd;
	size_t			size;

	index_cmd = 0;
	while (index_cmd < nb_cmd)
	{
		size = copy_size(command_list, index_cmd);
		tmp = (char *)malloc(sizeof(char) * (size + 1));
		if (tmp == NULL)
		{
			ft_free_strs(command_list);
			return (NULL);
		}
		*tmp = '\0';
		copy_command(command_list[index_cmd], tmp);
		free(command_list[index_cmd]);
		command_list[index_cmd] = tmp;
		index_cmd++;
	}
	return (command_list);
}
