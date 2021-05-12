#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

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
	exit(0);
}

void	test_stat(void)
{
	struct stat	statbuf;

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

int	main(void)
{
	int			fd = open("test_file", O_RDONLY);

	if (fd == -1)
		die("test_file", errno);
	close(fd);
	return (0);
}