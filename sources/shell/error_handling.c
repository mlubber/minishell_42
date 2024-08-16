#include "../../include/minishell.h"

static char	*ft_errorjoin(char const *s1, char const *s2)
{
	int		i;
	int		o;
	char	*p;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	o = ft_strlen(s1) + ft_strlen(s2);
	p = malloc((o + 4) * sizeof(char));
	if (!p)
		return (NULL);
	while (*s1)
		p[i++] = *s1++;
	p[i++] = ':';
	p[i++] = ' ';
	while (*s2)
		p[i++] = *s2++;
	p[i++] = '\n';
	p[i] = '\0';
	return (p);
}

void	handle_error(char *str)
{
	char	*err_msg;

	err_msg = NULL;
	if (str != NULL)
	{
		err_msg = ft_errorjoin(str, strerror(errno));
		if (err_msg == NULL)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			exit(errno);
		}
		write(2, err_msg, ft_strlen(err_msg));
		free(err_msg);
	}
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
}
