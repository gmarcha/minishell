#include "minishell.h"

int	shell_execution(char **args)
{
	(void)args;
	return (0);
}

void	shell_loop(void)
{
	char			*line;
	char			**args;
	int				ret;

	line = 0;
	while (1)
	{
		write(1, "$>", 2);
		shell_line(0, &line);
		args = shell_split(line, " \t\v\n\r\f\a");
		ret = shell_execution(args);
		(void)ret;
		write(1, line, ft_strlen(line));
		ft_free_strs(args);
		free(line);
	}
}

int	main(int argc, char *argv[])
{
	(void)argc;(void)argv;
	shell_loop();
	return (0);
}