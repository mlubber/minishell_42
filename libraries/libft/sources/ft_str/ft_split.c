/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 10:32:23 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/17 10:39:40 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countwords(char const *s, char c)
{
	size_t	wordcount;
	int		space;

	wordcount = 0;
	space = 1;
	while (*s)
	{
		if (*s != c && space == 1)
		{
			space = 0;
			wordcount++;
		}
		else if (*s == c)
		{
			space = 1;
		}
		s++;
	}
	return (wordcount);
}

static char	*copywords(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (n == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == 0)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**clearmem(char **strlist)
{
	int	i;

	i = 0;
	while (strlist[i])
	{
		free(strlist[i]);
		i++;
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strlist;
	size_t	i;
	size_t	j;
	size_t	save;

	i = 0;
	j = 0;
	strlist = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!strlist)
		return (NULL);
	while (i < countwords(s, c) && s[j] != '\0')
	{
		while (s[j] == c)
			j++;
		save = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		strlist[i] = copywords(&s[save], j - save);
		if (strlist[i] == 0)
			return (clearmem(strlist));
		i++;
	}
	strlist[i] = NULL;
	return (strlist);
}
