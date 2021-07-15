/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 17:20:10 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 17:20:10 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_line(char *line_content, t_var *env, int exit_status)
{
	char			*line_expand;

	(void)env; (void)exit_status;
	line_expand = ft_strdup(line_content);
	free(line_content);
	if (line_expand == NULL)
		return (NULL);
	return (line_expand);
}
