/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 03:10:44 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/05 03:10:44 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	p_name(char **error, char *name, char *errmsg, int errnum)
{
	if (name != NULL || errmsg != NULL || errnum != 0)
	{
		*error = ft_strconcat(error, name);
		if (*error == NULL)
			return (1);
	}
	return (0);
}

static int	p_errmsg(char **error, char *errmsg)
{
	if (errmsg != NULL)
	{
		*error = ft_strconcat(error, ": ");
		if (*error == NULL)
			return (1);
		*error = ft_strconcat(error, errmsg);
		if (*error == NULL)
			return (1);
	}
	return (0);
}

static int	p_errnum(char **error, int errnum)
{
	if (errnum != 0)
	{
		*error = ft_strconcat(error, ": ");
		if (*error == NULL)
			return (1);
		*error = ft_strconcat(error, strerror(errnum));
		if (*error == NULL)
			return (1);
	}
	return (0);
}

void	p_error(char *name, char *errmsg, int errnum)
{
	char			*error;

	error = NULL;
	if (p_name(&error, name, errmsg, errnum) == 1)
		return ;
	if (p_errmsg(&error, errmsg) == 1)
		return ;
	if (p_errnum(&error, errnum) == 1)
		return ;
	if (name != NULL || errmsg != NULL || errnum != 0)
	{
		error = ft_strconcat(&error, "\n");
		if (error == NULL)
			return ;
		ft_putstr_fd(error, 2);
	}
	free(error);
}
