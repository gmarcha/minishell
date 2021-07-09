/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 23:18:48 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/08 23:18:48 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*line_read(char *line, char *prompt)
{
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	line = readline(prompt);
	if (line != NULL && *line != '\0')
		add_history(line);
	return (line);
}
