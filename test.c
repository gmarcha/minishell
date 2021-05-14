#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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

int	exec(t_cmd *cmd, int nb_cmd)
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
			xexecve(cmd[i].args[0], cmd[i].args, 0);
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

int	main(void)
{
	t_cmd			cmd[] = {
		{
			.args = (char *[]){"/usr/bin/cat", "test_file.c", 0},
			.in_fd = 0,
			.out_fd = 1
		},
		{
			.args = (char *[]){"/usr/bin/grep", "include", 0},
			.in_fd = 0,
			.out_fd = 1
		},
		{
			.args = (char *[]){"/usr/bin/awk", "{count++} END {print count}", 0},
			.in_fd = 0,
			.out_fd = 1
		}
	};
	exec(cmd, sizeof(cmd) / sizeof(cmd[0]));
	return (0);
}
