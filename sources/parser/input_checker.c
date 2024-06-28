/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 16:35:52 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/24 12:43:13 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes(char *cmdline)
{
	int		i;
	char	quote;

	i = 0;
	while (cmdline[i])
	{
		if (cmdline[i] == '\'' || cmdline[i] == '"')
		{
			quote = cmdline[i];
			i++;
			while (cmdline[i] != quote)
			{
				if (cmdline[i] == '\0')
					return (2);
				i++;
			}
			i++;
		}
		if (cmdline[i] != '\0')
			i++;
	}
	return (0);
}

int	check_redirs(char *cmdline)
{
	int	i;

	i = 0;
	while (cmdline[i])
	{
		if (cmdline[i] == '\'' || cmdline[i] == '"')
			i += skip_quotes(cmdline + i, cmdline[i]);
		else if (cmdline[i] == '>' || cmdline[i] == '<')
		{
			i++;
			if (cmdline[i] == cmdline[i - 1])
				i++;
			i += check_whitespace(cmdline + i, 0);
			if (cmdline[i] == '>' || cmdline[i] == '<' || cmdline[i] == '|' || cmdline[i] == '\0')
				return (2);
		}
		if (cmdline[i] != '\0')
			i++;
	}
	return (0);
}

int	check_pipes(char *cmdline)
{
	int	i;

	i = 0;
	while (cmdline[i])
	{
		if (cmdline[i] == '\'' || cmdline[i] == '"')
			i += skip_quotes(cmdline + i, cmdline[i]);
		else if (cmdline[i] == '|')
		{
			i++;
			i += check_whitespace(cmdline + i, 0);
			if (cmdline[i] == '|' || cmdline[i] == '\0')
				return (2);
		}
		if (cmdline[i] != '\0')
			i++;
	}
	return (0);
}

int	check_first_cmd(char *cmdline)
{
	int	i;

	i = 0;
	while (cmdline[i] != '\0')
	{
		i += check_whitespace(cmdline + i, 0);
		if (cmdline[i] == '\'' || cmdline[i] == '"')
			i += skip_quotes(cmdline + i, cmdline[i]);
		else if (cmdline[i] == '>' || cmdline[i] == '<')
			i += skip_file_or_word(cmdline + i, cmdline[i]);
		else if (ft_isalnum(cmdline[i]) || cmdline[i] == '_')
		{
			while (ft_isalnum(cmdline[i]) || cmdline[i] == '_')
				i++;
			if (!check_whitespace(NULL, cmdline[i]) && !char_check(cmdline))
				return (2);
			while (cmdline[i] != '\0' && cmdline[i] != '|')
				i++;
		}
		else
			return (2);
		if (cmdline[i] != '\0')
			i++;
	}
	return (0);
}

int	input_checker(char **cmdline)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (*cmdline[i] != '\0')
		if (cmdline[i++] == '&') // Not sure if we need to be able to handle &
			x = 2;
	i = 0;
	while (ft_is_whitespace(*cmdline[i]))
		i++;
	if (*cmdline[i] == '\0')
		x = 1;
	else if (check_quotes(cmdline + i) == 2 || check_first_cmd(cmdline + i) == 2 || check_pipes(cmdline + i) == 2 || check_redirs(cmdline + i) == 2)
		x = 2;
	if (x > 0)
	{
		if (x == 2)
			printf("Syntax error!\n");
		free (*cmdline);
		return (1);
	}
	return (0);
}
