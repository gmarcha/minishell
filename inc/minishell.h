#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

# define PROGRAM_NAME	"minishell"

typedef enum e_redirect
{
	NO_REDIRECTION,
	SIMPLE_REDIRECTION,
	DOUBLE_REDIRECTION
}				t_redirect;

typedef struct s_cmd
{
	char			**args;
	int				fd_in;
	int				fd_out;
	int				save_stdin;
	int				save_stdout;
	t_redirect		redirect_in;
	t_redirect		redirect_out;
	char			*name_in;
	char			*name_out;
	pid_t			pid_process;
	int				exit_status;
}					t_cmd;


void	close_cmd_fd(t_cmd *cmd, size_t nb_cmd);

void	destroy_process(t_cmd *cmd, size_t nb_cmd, char **envp, int exit_status);

void	p_error(char *name, char *errmsg, int errnum);

void	execute_path(t_cmd *cmd, size_t nb_cmd, size_t index_cmd, char **envp);

void	execute(t_cmd *cmd, size_t nb_cmd, size_t index_cmd, char **envp);

int		launch_builtin(t_cmd *cmd, size_t nb_cmd, size_t index_cmd, char **envp);

int		launch(t_cmd *cmd, size_t nb_cmd, char **envp, int exit_status);

char	*line_read(char *line, char *prompt);

int		redirect(t_cmd *cmd, size_t nb_cmd, size_t index_cmd, int exit_status);

int		reset_redirection(t_cmd *cmd, size_t nb_cmd, size_t index_cmd);

int		wait_process(t_cmd *cmd, size_t nb_cmd);

#endif