/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/26 16:58:48 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/26 16:59:09 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	skip_quotes(char *cmdline, char quote)
{
	int	i;

	i = 1;
	while (cmdline[i] != quote)
		i++;
	i++;
	return (i);
}

int	skip_file_or_word(char *cmdline, char c)
{
	int	i;

	if (c == '<' || c == '>')
	{
		i = 1;
		if (cmdline[i] == c)
			i = 2;
		i += check_whitespace(cmdline + i, 0);
		while (cmdline[i] && !check_whitespace(NULL, cmdline[i]) && !char_check(cmdline + i))
			i++;
		return (i);		
	}
	else
	{
		i = 0;
		while (cmdline[i] && !check_whitespace(NULL, cmdline[i]) && !char_check(cmdline + i))
			i++;
		return (i);
	}
}

int	char_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (1);
	if (str[i] == '<' || str[i] == '>')
	{
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			return (2);
		return (1);
	}
	return (0);
}
