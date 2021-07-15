/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 22:26:28 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 22:26:28 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_command(char **command_list, size_t nb_cmd)
{
	t_cmd			*cmd;
	char			***command_redirect;
	size_t			i;

	command_redirect = split_command(command_list, nb_cmd);
	if (command_redirect == NULL)
		return (NULL);
	cmd = create_command(nb_cmd, command_redirect);
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (i < nb_cmd)
		cmd[i++].nb_cmd = nb_cmd;
	if (parse_command(cmd, nb_cmd, command_redirect) == -1)
		return (NULL);
	return (cmd);
}

t_cmd	*parse_line(char **line, t_var *env, int *exit_status)
{
	char			*line_content;
	char			*line_expand;
	char			**command_list;
	size_t			nb_cmd;

	line_content = handle_unclosed_quotes(line);
	if (line_content == NULL)
		return (NULL);
	line_expand = expand_line(line_content, env, *exit_status);
	free(line_content);
	if (line_expand == NULL)
		return (NULL);
	if (is_line_not_empty(line_expand, exit_status) == -1)
		return (NULL);
	command_list = split_line(line_expand);
	if (command_list == NULL)
		return (NULL);
	nb_cmd = ft_strslen((const char **)command_list);
	return (init_command(command_list, nb_cmd));
}
