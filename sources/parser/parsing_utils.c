/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/26 16:58:48 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/16 16:05:23 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	skip_quotes(char *cmdline, char quote)
{
	int	i;

	i = 1;
	while (cmdline[i] != quote)
		i++;
	return (++i);
}

int	char_check(char *str)
{
	if (str[0] == '|')
		return (1);
	if (str[0] == '<' || str[0] == '>')
	{
		if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
			return (2);
		return (1);
	}
	return (0);
}

int	skip_file_or_word(char *cmdline, char c, int i)
{
	if (c == '<' || c == '>')
	{
		i++;
		if (cmdline[i] == c)
			i++;
	}
	i += check_whitespace(cmdline + i, 0);
	while (cmdline[i] && !check_whitespace(NULL, cmdline[i]) && !char_check(cmdline + i))
	{
		if (cmdline[i] == '\'' || cmdline[i] == '"')
			i += skip_quotes(cmdline + i, cmdline[i]);
		else
			i++;
	}
	return (i);
}
