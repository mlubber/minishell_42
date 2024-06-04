/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_reader.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 10:12:45 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 16:32:33 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	size_t	j;

	j = 0;
	while (str[i + j])
	{
		j += ft_handle_quotes(i, str, 34);
		j += ft_handle_quotes(i, str, 39);
		if (ft_is_whitespace(str[i + j]) || i + j > ft_strlen(str) - 1
			|| str[i + j] == 34 || str[i + j] == 39)
			break ;
		else
			j++;
	}
	ft_add_node(ft_substr(str, i, j), lexer_list); // Add fail check
	return (j);
}

int	ft_reader(t_tools *tools)
{
	int	i;
	int	j;

	i = 0;
	while (tools->full_string[i])
	{
		j = 0;
		i = i + ft_skip_spaces(i, tools->full_string);
		j = ft_read_word(i, tools->full_string, &tools->lexer_list);
		i = i + j;
	}
	return (1);
}
