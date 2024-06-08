/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_splitter.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 10:48:45 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/07 17:35:59 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_quotes(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
	{
		while (str[i] != '\'' && str[i] != '\0')
			i++;
		if (str[i] != '\'')
			return (-1);
		return (i);
	}
	else if (str[i] == '\'')
	{
		while (str[i] != '"' && str[i] != '\0')
			i++;
		if (str[i] != '"')
			return (-1);
		return (i);
	}
	return (0);
}


static int	char_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (1);
	else if (str[i] == '$')
		while (str[i] != ' ' && str[i] != '\0')
			i++;
	else if (str[i] == '<' || str[i] == '>')
	{
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			return (2);
		return (1);
	}
	else if (str[i] == '\'' || str[i] == '"')
		return (check_quotes(str));
	return (0);
}


static int	ft_wordcount(char *str)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (str[i])
	{
		if (!ft_is_whitespace(str[i]))
		{
			o++;
			if (char_check(str + i) > 0)
				i += char_check(str + i);
			else
				while (!ft_is_whitespace(str[i]) && str[i] != '\0' && char_check(str + i) == 0)
					i++;
		}
		else
			i++;
	}
	return (o);
}

static int	ft_wordlength(char *str)
{
	int	i;

	i = 0;
	if (char_check(str) > 0)
	{
		i = char_check(str);
		return (i);
	}
	else
	{
		while (!ft_is_whitespace(str[i]) && str[i] != '\0' && char_check(str + i) == 0)
			i++;
	}
	return (i);
}

// Currently working but will be replaced for a command table linked list
char	**input_splitter(char *str)
{
	int		i;
	int		len;
	char	**split_parts;

	i = 0;
	split_parts = malloc((ft_wordcount(str) + 1) * sizeof(char *));
	if (split_parts == NULL)
		return (NULL);
	while (*str)
	{
		if (ft_is_whitespace(*str))
			str++;
		else
		{
			len = ft_wordlength(str);
			split_parts[i] = malloc((len + 1) * sizeof(char));
			if (split_parts[i] == NULL)
				return (ft_free_2d_arr(&split_parts, 0));
			ft_strlcpy(split_parts[i++], str, len + 1);
			str += len;
		}
	}
	split_parts[i] = NULL;
	return (split_parts);
}
