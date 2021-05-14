#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <mcheck.h>

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

void	die(char *errmsg, int errnum)
{
	if (errmsg || errnum)
		ft_putstr_fd(PROGRAM_NAME, 2);
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

void	test_stat(void)
{
	struct stat		statbuf;

	if (stat("test_file", &statbuf) == -1)
		die("fstat", errno);
	printf("%lu\n", statbuf.st_dev);
	printf("%lu\n", statbuf.st_ino);
	printf("%u\n", statbuf.st_mode);
	printf("%lu\n", statbuf.st_nlink);
	printf("%u\n", statbuf.st_uid);
	printf("%u\n", statbuf.st_gid);
	printf("%lu\n", statbuf.st_rdev);
	printf("%ld\n", statbuf.st_size);
	printf("%ld\n", statbuf.st_blksize);
	printf("%ld\n", statbuf.st_blocks);
	printf("%ld\n", statbuf.st_atime);
	printf("%ld\n", statbuf.st_mtime);
	printf("%ld\n", statbuf.st_ctime);
}

pid_t	xfork(void)
{
	pid_t			child;

	child = fork();
	if (child == (pid_t)-1)
		die("fork()", errno);
	return (child);
}

void	xpipe(int p_fd[])
{
	if (pipe(p_fd) == -1)
		die("pipe()", errno);
}

void	xdup2(int fd, int _fileno)
{
	if (dup2(fd, _fileno) == -1)
		die("dup2()", errno);
}

void	xexecve(char *pathname, char *const *args, char *const *env)
{
	execve(pathname, args, env);
	die("execve()", errno);
}

int	ispath(char *dir_name, char *file_name)
{
	DIR				*dir;
	struct dirent	*ent;

	dir = opendir(dir_name);
	if (dir == 0)
	{
		if (errno == ENOENT)
			return (0);
		die("opendir()", errno);
	}
	while (1)
	{
		errno = 0;
		ent = readdir(dir);
		if (ent == 0 && errno != 0)
			die("readdir()", errno);
		if (ent == 0)
			break ;
		if (ft_strncmp(ent->d_name, ".", 1) == 0 || ft_strncmp(ent->d_name, "..", 2) == 0)
			continue ;
		if (ft_strncmp(ent->d_name, file_name, 260) == 0)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

int	exec(t_cmd *cmd, int nb_cmd, char **envp)
{
	int		p_fd[2];
	pid_t	pid;
	char	**env_path;
	int		i;
	int		j;

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
			env_path = ft_split(getenv("PATH"), ':');
			if (env_path == 0)
				die("ft_split()", errno);
			j = 0;
			while (env_path[j])
			{
				if (ispath(env_path[j], cmd[i].args[0]) == 1)
				{
					char		*tmp;
					tmp = ft_strjoin(env_path[j], "/");
					free(env_path[j]);
					env_path[j] = tmp;
					xexecve(ft_strjoin(env_path[j], cmd[i].args[0]), cmd[i].args, envp);
				}
				j++;
			}
			ft_free_strs(env_path);
			xexecve(cmd[i].args[0], cmd[i].args, envp);
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
	(void)argc;(void)argv;
	t_cmd			cmd[] = {
		{
			.args = (char *[]){"cat", "test_file.c", 0},
			.in_fd = 0,
			.out_fd = 1
		},
		{
			.args = (char *[]){"grep", "include", 0},
			.in_fd = 0,
			.out_fd = 1
		},
		{
			.args = (char *[]){"awk", "{count++} END {print count}", 0},
			.in_fd = 0,
			.out_fd = 1
		}
	};
	exec(cmd, sizeof(cmd) / sizeof(cmd[0]), envp);
	return (0);
}
