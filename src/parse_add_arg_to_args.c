/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_add_arg_to_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 21:00:49 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 21:00:49 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_args(char *arg)
{
	char			**new_args;

	new_args = (char **)malloc(sizeof(char *) * 2);
	if (new_args == NULL)
		return (NULL);
	new_args[1] = NULL;
	new_args[0] = ft_strdup(arg);
	if (new_args[0] == NULL)
	{
		free(new_args);
		return (NULL);
	}
	return (new_args);
}

static char	**destroy_args(char **input_args, char **new_args)
{
	if (input_args != NULL)
		ft_free_strs(input_args);
	if (new_args != NULL)
		ft_free_strs(new_args);
	return (NULL);
}

static char	**copy_args(char **input_args, char **new_args, char *arg,
	size_t size)
{
	size_t			i;

	i = 0;
	while (i < size)
	{
		new_args[i] = ft_strdup(input_args[i]);
		if (new_args[i] == NULL)
			return (destroy_args(input_args, new_args));
		i++;
	}
	new_args[i] = ft_strdup(arg);
	if (new_args[i] == NULL)
		return (destroy_args(input_args, new_args));
	return (new_args);
}

char	**add_arg_to_args(char **input_args, char *arg)
{
	char			**new_args;
	size_t			size;

	if (input_args == NULL)
		return (create_args(arg));
	else
	{
		size = ft_strslen((const char **)input_args);
		new_args = (char **)malloc(sizeof(char *) * (size + 2));
		if (new_args == NULL)
			return (destroy_args(input_args, NULL));
		new_args[size + 1] = NULL;
		if (copy_args(input_args, new_args, arg, size) == NULL)
			return (NULL);
		ft_free_strs(input_args);
		return (new_args);
	}
}
