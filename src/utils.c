#include "minishell.h"

int	ft_strlen(const char *s)
{
	int			i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int				i;

	i = -1;
	while (s[++i])
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	return (0);
}

char	*ft_strdup(char *s)
{
	char			*d;
	int				i;

	i = 0;
	while (s[i])
		i++;
	d = (char *)malloc(i + 1);
	if (d == 0)
		return (0);
	i = -1;
	while (s[++i])
		d[i] = s[i];
	d[i] = 0;
	return (d);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == 0)
		return (0);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = 0;
	return (str);
}

char	*ft_substr(char *s, unsigned int start, unsigned int len)
{
	char			*str;
	unsigned int	len_s;
	unsigned int	i;

	len_s = ft_strlen(s);
	if (len_s < start)
		str = (char *)malloc(1);
	else if (len_s - start < len)
		str = (char *)malloc(len_s - start + 1);
	else
		str = (char *)malloc(len + 1);
	if (str == 0)
		return (0);
	i = 0;
	if (start < len_s)
	{
		while (s[i + start] && i < len)
		{
			str[i] = s[i + start];
			i++;
		}
	}
	str[i] = 0;
	return (str);
}
