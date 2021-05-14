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

int	exec(char *const cat_args[], char *const grep_args[])
{
	int		p_fd[2];
	pid_t	child1;
	pid_t	child2;

	xpipe(p_fd);
	child1 = xfork();
	if (child1 == 0)
	{
		xdup2(p_fd[1], 1);
		close(p_fd[0]);
		close(p_fd[1]);
		xexecve("/usr/bin/cat", cat_args, 0);
	}
	else
	{
		child2 = xfork();
		if (child2 == 0)
		{
			xdup2(p_fd[0], 0);
			close(p_fd[0]);
			close(p_fd[1]);
			xexecve("/usr/bin/grep", grep_args, 0);
		}
		else
		{
			close(p_fd[0]);
			close(p_fd[1]);
			wait(0);
			wait(0);
		}
	}
	return (0);
}

int	main(void)
{
	exec(
		(char *const []){"cat", "test_file.c", 0},
		(char *const []){"grep", "main", 0}
	);
	return (0);
}
