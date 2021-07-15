/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skip_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:11:18 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/14 20:11:18 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *command, size_t *i)
{
	if (command[*i] == '\'')
		while (command[++(*i)] != '\'')
			;
	else if (command[*i] == '"')
		while (command[++(*i)] != '"')
			;
}
