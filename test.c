#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "libft/libft.h"

#define PROGRAM_NAME	"test"

typedef struct s_cmd
{
	char			**args;
	int				in_fd;
	int				out_fd;
}					t_cmd;

void	*ft_free_strs(char **strs)
{
	size_t			i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (0);
}

void	die(char *name, char *errmsg, int errnum)
{
	if (errmsg || errnum)
		ft_putstr_fd(name, 2);
	if (errmsg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(errmsg, 2);
	}
	if (errnum)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errnum), 2);
	}
	ft_putendl_fd("", 2);

	exit(1);
}

pid_t	xfork(void)
{
	pid_t			child;

	child = fork();
	if (child == (pid_t)-1)
		die(PROGRAM_NAME, "fork()", errno);
	return (child);
}

void	xpipe(int p_fd[])
{
	if (pipe(p_fd) == -1)
		die(PROGRAM_NAME, "pipe()", errno);
}

void	xdup2(int fd, int _fileno)
{
	if (dup2(fd, _fileno) == -1)
		die(PROGRAM_NAME, "dup2()", errno);
}

void	xexecve(char *pathname, char *const *args, char *const *env)
{
	execve(pathname, args, env);
	die(PROGRAM_NAME, "execve()", errno);
}

DIR	*xopendir(char *dir_name)
{
	DIR				*dir;

	dir = opendir(dir_name);
	if (dir == 0)
	{
		if (errno == ENOENT)
			return (0);
		die(PROGRAM_NAME, "opendir()", errno);
	}
	return (dir);
}

struct dirent	*xreaddir(DIR *dir)
{
	struct dirent	*ent;

	errno = 0;
	ent = readdir(dir);
	if (ent == 0 && errno != 0)
		die(PROGRAM_NAME, "readdir()", errno);
	return (ent);
}

int	exec_echo(t_cmd cmd)
{
	int				i;
	int				opt;

	opt = 0;
	if (cmd.args[1] && ft_strncmp(cmd.args[1], "-n", 3) == 0)
	{
		opt = 1;
		cmd.args++;
	}
	i = 1;
	while (cmd.args[i])
	{
		if (i > 1)
			ft_putstr_fd(" ", cmd.out_fd);
		ft_putstr_fd(cmd.args[i], cmd.out_fd);
		i++;
	}
	if (opt == 0)
		ft_putendl_fd("", cmd.out_fd);
	return (1);
}

int	exec_cd(t_cmd cmd)
{
	if (cmd.args[1] == 0)
	{
		if (chdir(getenv("HOME")) == -1)
			die(PROGRAM_NAME, "chdir()", errno);
		exit(0);
	}
	if (cmd.args[2] != 0)
		die("cd", "too many arguments", 0);
	if (chdir(cmd.args[1]) == -1)
		die(PROGRAM_NAME, "chdir()", errno);
	return (1);
}

int	exec_pwd(t_cmd cmd)
{
	char			buf[1024];

	if (cmd.args[1] != 0)
		die("pwd", "too many arguments", 0);
	if (getcwd(buf, sizeof(buf)) == 0)
		die(PROGRAM_NAME, "getcwd()", errno);
	ft_putendl_fd(buf, cmd.out_fd);
	return (1);
}

// int	exec_export(t_cmd cmd)
// {
// 	return (1);
// }

// int	exec_unset(t_cmd cmd)
// {
// 	return (1);
// }

// int	exec_env(t_cmd cmd)
// {
// 	return (1);
// }

// int	exec_exit(t_cmd cmd)
// {
// 	return (1);
// }

int	isbuiltin(t_cmd cmd)
{
	if (ft_strncmp(cmd.args[0], "echo", 5) == 0)
		return (exec_echo(cmd));
	if (ft_strncmp(cmd.args[0], "cd", 3) == 0)
		return (exec_cd(cmd));
	if (ft_strncmp(cmd.args[0], "pwd", 4) == 0)
		return (exec_pwd(cmd));
	// if (ft_strncmp(cmd.args[0], "export", 7) == 0)
	// 	return (exec_export(cmd));
	// if (ft_strncmp(cmd.args[0], "unset", 6) == 0)
	// 	return (exec_unset(cmd));
	// if (ft_strncmp(cmd.args[0], "env", 4) == 0)
	// 	return (exec_env(cmd));
	// if (ft_strncmp(cmd.args[0], "exit", 5) == 0)
	// 	return (exec_exit(cmd));
	return (0);
}

int	ispath(char *dir_name, char *file_name)
{
	DIR				*dir;
	struct dirent	*ent;

	dir = xopendir(dir_name);
	if (dir == 0)
		return (0);
	while (1)
	{
		ent = xreaddir(dir);
		if (ent == 0)
			break ;
		if (ft_strncmp(ent->d_name, ".", 2) == 0 || ft_strncmp(ent->d_name, "..", 3) == 0)
			continue ;
		if (ft_strncmp(ent->d_name, file_name, 260) == 0)
			return (closedir(dir) * 0 + 1);
	}
	return (closedir(dir) * 0);
}

void	exec(t_cmd cmd, char **envp)
{
	char	**env_path;
	char	*tmp;
	int		j;

	if (isbuiltin(cmd))
		exit(0);
	env_path = ft_split(getenv("PATH"), ':');
	if (env_path == 0)
		die(PROGRAM_NAME, "ft_split()", errno);
	j = 0;
	while (env_path[j])
	{
		if (ispath(env_path[j], cmd.args[0]) == 1)
		{
			tmp = ft_strjoin(env_path[j], "/");
			free(env_path[j]);
			env_path[j] = tmp;
			xexecve(ft_strjoin(env_path[j], cmd.args[0]), cmd.args, envp);
		}
		j++;
	}
	ft_free_strs(env_path);
	xexecve(cmd.args[0], cmd.args, envp);
}

int	launch(t_cmd *cmd, int nb_cmd, char **envp)
{
	int		p_fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	while (i < nb_cmd)
	{
		if (i < nb_cmd - 1)
		{
			xpipe(p_fd);
			cmd[i].out_fd = p_fd[1];
			cmd[i + 1].in_fd = p_fd[0];
		}
		pid = xfork();
		if (pid == 0)
		{
			if (i != 0)
			{
				xdup2(cmd[i].in_fd, 0);
				close(cmd[i].in_fd);
				close(cmd[i - 1].out_fd);
			}
			if (i < nb_cmd - 1)
			{
				xdup2(cmd[i].out_fd, 1);
				close(cmd[i].out_fd);
				close(cmd[i + 1].in_fd);
			}
			exec(cmd[i], envp);
		}
		else
		{
			if (cmd[i].in_fd != 0)
				close(cmd[i].in_fd);
			if (cmd[i].out_fd != 1)
				close(cmd[i].out_fd);
			i++;
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;(void)argv;(void)envp;
	// t_cmd			cmd[] = {
	// 	{
	// 		.args = (char *[]){"cd", "libftnu", 0},
	// 		.in_fd = 0,
	// 		.out_fd = 1
	// 	}
	// };
	// t_cmd			cmd[] = {
	// 	{
	// 		.args = (char *[]){"cat", "test_file", 0},
	// 		.in_fd = 0,
	// 		.out_fd = 1
	// 	},
	// 	{
	// 		.args = (char *[]){"grep", "include", 0},
	// 		.in_fd = 0,
	// 		.out_fd = 1
	// 	},
	// 	{
	// 		.args = (char *[]){"awk", "{count++} END {print count}", 0},
	// 		.in_fd = 0,
	// 		.out_fd = 1
	// 	}
	// };
	// launch(cmd, sizeof(cmd) / sizeof(cmd[0]), envp);

	// struct termios	*termios_p;

	printf("%s\n", ttyname(1));
	return (0);
}
