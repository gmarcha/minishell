#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"

char	*line_read(char *line)
{
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	line = readline("$> ");
	if (line != NULL && *line != '\0')
		add_history(line);
	return (line);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

int		main(void)
{
	char			*line;
	int				exit_status;

	if (signal(SIGINT, sig_handler) == SIG_ERR
		|| signal(SIGQUIT, sig_handler) == SIG_ERR)
		return (0);
	exit_status = 0;
	line = NULL;
	line = line_read(line);
	while (line != NULL)
	{
		printf("%s\n", line);
		line = line_read(line);
	}
	ft_putstr_fd("exit\n", 1);
	return (exit_status);
}