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

int	exec(char *const cat_args[], char *const grep_args[])
{
	int		p_fd[2];
	pid_t	child1;
	pid_t	child2;

	if (pipe(p_fd) == -1)
		die("pipe()", errno);
	child1 = fork();
	if (child1 == -1)
		die("fork()", errno);
	else if (child1 == 0)
	{
		if (dup2(p_fd[1], 1) == -1)
			die("dup2()", errno);
		close(p_fd[0]);
		close(p_fd[1]);
		if (execve("/usr/bin/cat", cat_args, 0) == -1)
			die("execve()", errno);
	}
	else
	{
		child2 = fork();
		if (child2 == -1)
			die("fork()", errno);
		else if (child2 == 0)
		{
			if (dup2(p_fd[0], 0) == -1)
				die("dup2()", errno);
			close(p_fd[0]);
			close(p_fd[1]);
			if (execve("/usr/bin/grep", grep_args, 0) == -1)
				die("execve()", errno);
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
	int				ret;

	ret = exec(
		(char *const []){"cat", "test_file", 0},
		(char *const []){"grep", "42", 0}
	);
	printf("%d\n", ret);
}
