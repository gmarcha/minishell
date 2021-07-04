#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*line_read(char *line)
{
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	line = readline("$>");
	if (line != NULL && *line != '\0')
		add_history(line);
	return (line);
}

int		main(void)
{
	char			*line;

	using_history();
	while (1)
	{
		line = readline("$>");
		printf("%s\n", line);
	}
	free(line);
	return (0);
}