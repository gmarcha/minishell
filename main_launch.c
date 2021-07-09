/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 03:10:00 by gamarcha          #+#    #+#             */
/*   Updated: 2021/07/05 03:10:00 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

// cat < test_file | tr -d "0" | grep include | tr -d "#" > out2 | awk '{count++} END {print count}'

int	main(int argc, char **argv, char **envp)
{
	t_cmd			cmd[] = {
		{
			.args = (char *[]){"cat", 0},
			.fd_in = 0,
			.fd_out = 1,
			.save_stdin = 0,
			.save_stdout = 1,
			.redirect_in = SIMPLE_REDIRECTION,
			.redirect_out = NO_REDIRECTION,
			.name_in = "test_file",
			.name_out = NULL,
			.pid_process = 0,
			.exit_status = 0
		},
		{
			.args = (char *[]){"tr", "-d", "0", 0},
			.fd_in = 0,
			.fd_out = 1,
			.save_stdin = 0,
			.save_stdout = 1,
			.redirect_in = NO_REDIRECTION,
			.redirect_out = NO_REDIRECTION,
			.name_in = NULL,
			.name_out = NULL,
			.pid_process = 0,
			.exit_status = 0
		},
		{
			.args = (char *[]){"grep", "include", 0},
			.fd_in = 0,
			.fd_out = 1,
			.save_stdin = 0,
			.save_stdout = 1,
			.redirect_in = NO_REDIRECTION,
			.redirect_out = NO_REDIRECTION,
			.name_in = NULL,
			.name_out = NULL,
			.pid_process = 0,
			.exit_status = 0
		},
		{
			.args = (char *[]){"tr", "-d", "#", 0},
			.fd_in = 0,
			.fd_out = 1,
			.save_stdin = 0,
			.save_stdout = 1,
			.redirect_in = NO_REDIRECTION,
			.redirect_out = SIMPLE_REDIRECTION,
			.name_in = NULL,
			.name_out = "out2",
			.pid_process = 0,
			.exit_status = 0
		},
		{
			.args = (char *[]){"ls", "-la", 0},
			.fd_in = 0,
			.fd_out = 1,
			.save_stdin = 0,
			.save_stdout = 1,
			.redirect_in = NO_REDIRECTION,
			.redirect_out = NO_REDIRECTION,
			.name_in = NULL,
			.name_out = NULL,
			.pid_process = 0,
			.exit_status = 0
		}
	};

	(void)argc;(void)argv;
	return (launch(cmd, sizeof(cmd) / sizeof(cmd[0]), envp, 0));
}
