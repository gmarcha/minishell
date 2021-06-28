#include "libft/libft.h"
#include <stdio.h>
#include <string.h>

void	test(t_list **global_ref)
{
	char			*str;

	str = (char *)get_index(global_ref, "hello_world_str");
	printf("OP global: %s\n", str);
	free_index(global_ref, "strs");
}

int	main(void)
{
	t_list			*global_ref;
	char			*s2;
	char			**strs;

	global_ref = NULL;

	s2 = (char *)malloc_index(&global_ref, "hello_world_str", free, malloc(sizeof(char) * 13));
	if (s2 == NULL)
		malloc_destroy(&global_ref, NULL);
	memcpy(s2, "Hello World!", 13);
	printf("%s\n", s2);

	strs = (char **)malloc_index(&global_ref, "strs", ft_free_strs, ft_split("Hello World!", ' '));
	if (strs == NULL)
		malloc_destroy(&global_ref, NULL);
	for (size_t i = 0; strs[i] != NULL; i++)
		printf("%s\n", strs[i]);

	test(&global_ref);
	free_wrap(&global_ref, s2);
	// malloc_clear(&global_ref);
	return (0);
}
