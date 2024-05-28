/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_reader.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 10:12:45 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/28 12:51:17 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// size_t	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	size_t	i;
// 	char	*csrc;
// 	char	*cdest;

// 	i = 0;
// 	csrc = (char *) src;
// 	cdest = (char *) dest;
// 	if (!dest && !src)
// 		return (0);
// 	while (i < n)
// 	{
// 		cdest[i] = csrc[i];
// 		i++;
// 	}
// 	return (dest);
// }

// char	*ft_strdup(const char *str)
// {
// 	size_t	len;
// 	char	*alloc;

// 	len = (ft_strlen(str) + 1);
// 	alloc = (char *)malloc(len * sizeof(char));
// 	if (alloc == NULL)
// 		return (NULL);
// 	ft_memcpy(alloc, str, len);
// 	return (alloc);
// }

// char	*ft_substr(char const *str, unsigned int start, size_t len)
// {
// 	char	*substr;
// 	char	*newstr;
// 	size_t	strlen;
// 	size_t	i;

// 	strlen = ft_strlen(str);
// 	if (start > ft_strlen(str))
// 		return (ft_strdup(""));
// 	if (start + len < strlen)
// 		substr = (char *)malloc((len + 1) * sizeof(char));
// 	else
// 		substr = (char *)malloc((strlen - start + 1) * sizeof(char));
// 	if (substr == 0)
// 		return (0);
// 	i = start;
// 	newstr = substr;
// 	while ((i < start + len) && str[i])
// 	{
// 		*newstr = str[i];
// 		i++;
// 		newstr++;
// 	}
// 	*newstr = '\0';
// 	return (substr);
// }

int	ft_is_whitespace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	ft_skip_spaces(int i, char *str)
{
	int	j;

	j = 0;
	while (ft_is_whitespace(str[i + j]))
		j++;
	return (j);
}

int	ft_add_node(char *str, t_lexer **lexer_list)
{
	t_lexer	*node;

	node = ft_new_lexer_node(str);
	if (node == NULL)
		return (0);
	ft_lexer_add_back(lexer_list, node);
	return (1);
}

int	ft_read_word(int i, char *str, t_lexer **lexer_list)
{
	int		j;
	// char	*new_str;

	j = 0;
	while (str[i + j])
	{
		if (ft_is_whitespace(str[i + j]))
			break ;
		else
			j++;
	}
	ft_add_node(ft_substr(str, i, j), lexer_list);
	// new_str = ft_substr(str, i, j);
	// printf("[%s]\n", new_str);
	return (j);
}

int	ft_reader(t_tools *tools)
{
	int	i;
	int	j;

	i = 0;
	while (tools->args[i])
	{
		j = 0;
		i = i + ft_skip_spaces(i, tools->args);
		j = ft_read_word(i, tools->args, &tools->lexer_list);
		i = i + j;
	}
	return (1);
}

// int	main(void)
// {
// 	char	*string;
// 	int		i;
// 	int		j;

// 	string = "    Hello World    How   are you doing | help";
// 	i = 0;
// 	while (i < ft_strlen(string))
// 	{
// 		j = 0;
// 		i = i + ft_skip_spaces(i, string);
// 		j = ft_read_word(i, string);
// 		i = i + j;
// 	}
// 	return (0);
// }
