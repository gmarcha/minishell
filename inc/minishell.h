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
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

# define RESET			"\033[0m"
# define YELLOW			"\033[33m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36m"

# define PROGRAM_NAME	"minishell"
# define PROMPT			"\033[35m§¬ \033[36mminishell-42 \033[33mŸ \033[0m"

# define EMPTY_STR		""

# define EXIT_ARG_ERROR	": numeric argument required"
# define ENV_NAME_ERROR	"': not a valid identifier"
# define CD_DIR_ERROR	": No such file or directory"
# define CD_ARG_ERROR	"too many arguments"
# define CD_HOME_ERROR	"HOME not set"

extern volatile int	g_exit_status;

typedef enum e_redirect
{
	NO_REDIRECTION,
	SIMPLE_REDIRECTION,
	DOUBLE_REDIRECTION
}				t_redirect;

typedef struct s_cmd
{
	size_t			nb_cmd;
	size_t			index_cmd;
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

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct s_node
{
	char			c[2];
	char			*s;
	t_bool			free_s;
	size_t			len;
	struct s_node	*next;
}					t_node;

void	close_cmd_fd(t_cmd *cmd, size_t nb_cmd);
void	destroy_process(t_cmd *cmd, size_t nb_cmd, t_var **env,
			int exit_status);
void	p_error(char *name, char *errmsg, int errnum);
int		execute_builtin(t_cmd *cmd, size_t index_cmd, t_var **env,
			int exit_status);
int		execute_path(t_cmd *cmd, size_t index_cmd, t_var *env, char **envp);
void	execute(t_cmd *cmd, size_t index_cmd, t_var **env, int exit_status);
void	free_cmd(t_cmd *cmd, size_t nb_cmd);
void	free_sstrs(char ***command_redirect, size_t nb_cmd);
int		launch_builtin(t_cmd *cmd, size_t index_cmd, t_var **env,
			int exit_status);
int		heredoc(t_cmd *cmd, size_t index_cmd, t_var *env, int exit_status);
int		redirect(t_cmd *cmd, size_t index_cmd, t_var **env, int exit_status);
int		reset_redirection(t_cmd *cmd, size_t index_cmd);
int		wait_process(t_cmd *cmd, size_t nb_cmd);
int		launch(t_cmd *cmd, t_var **env, int exit_status);
char	*line_read(char *line, char *prompt);
char	**add_arg_to_args(char **input_args, char *arg);
int		parse_command(t_cmd *cmd, size_t nb_cmd, char ***command_redirect,
			t_var *env);
t_cmd	*create_command(size_t nb_cmd, char ***command_redirect);
char	*expand_line(char *line_content, t_var *env, int exit_status);
char	**expand_redirect_op(char **command_list, size_t nb_cmd);
char	*handle_unclosed_quotes(char **line);
int		is_line_not_empty(char *line_expand);
t_cmd	*parse_line(char **line, t_var *env);
int		remove_quotes(char **command);
void	skip_quotes(char *command, size_t *i);
char	***split_command(char **command_list, size_t nb_cmd);
char	**split_line(char *line_expand);

void	destroy_var(t_var *var);
void	clear_list(t_var **list);
t_bool	check_var_name(char *name);
t_var	*make_var(char *name, char *value);
t_var	*construct_globals(char **envp);
t_bool	add_var(t_var **list, char *name, char *value);
void	del_var(t_var **list, char *name);
char	*get_var(t_var *list, char *name);
t_bool	set_var(t_var *list, char *name, char *new_value);
char	**export_to_envp(t_var *globals);
t_bool	check_var_exist(t_var *list, char *name);

int		mini_cd(char **args, t_var *var_list);
int		mini_echo(char **args);
int		mini_env(char **args, t_var *var_list);
int		mini_exit(char **args, t_var **var_list_ptr, int exit_status);
int		mini_export(char **args, t_var **var_list_ptr);
int		mini_pwd(char **args, t_var *var_list);
int		mini_unset(char **args, t_var **var_list_ptr);

t_node	*new_node(char c, char *s, t_bool free_s);
void	*clear_nodes(t_node *start);
void	append_node(t_node **start_ptr, t_node *node);
char	*join_nodes(t_node *start);

#endif