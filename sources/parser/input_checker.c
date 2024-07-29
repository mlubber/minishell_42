/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 16:35:52 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/29 13:25:18 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_quotes(char *cmdline)
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
		}
		if (cmdline[i] != '\0')
			i++;
	}
	return (0);
}

static int	check_redirs(char *cmdline)
{
	int	i;

	i = 0;
	while (cmdline[i])
	{
		if (cmdline[i] == '\'' || cmdline[i] == '"')
			i += skip_quotes(cmdline + i, cmdline[i]);
		if (cmdline[i] == '<' || cmdline[i] == '>')
		{
			i++;
			if (cmdline[i] == cmdline[i - 1])
				i++;
			i += check_whitespace(cmdline + i, 0);
			if (char_check(cmdline + i) || cmdline[i] == '\0')
				return (2);
		}
		if (cmdline[i] != '\0' && cmdline[i] != '\'' && cmdline[i] != '"')
			i++;
	}
	return (0);
}

static int	check_pipes(t_shell *shell, char *cmdline)
{
	int	i;

	i = 0;
	if (cmdline[i] == '|')
		return (2);
	while (cmdline[i])
	{
		if (cmdline[i] == '\'' || cmdline[i] == '"')
			i += skip_quotes(cmdline + i, cmdline[i]);
		else if (cmdline[i] == '|')
		{
			i++;
			i += check_whitespace(cmdline + i, 0);
			if (cmdline[i] == '|')
				return (2);
			else if (cmdline[i] == '\0')
				return (finish_line(shell));
		}
		else if (cmdline[i] != '\0')
			i++;
	}
	return (0);
}

int	input_checker(t_shell *shell, char *cmdline)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	i += check_whitespace(cmdline, 0);
	if (cmdline[i] == '\0')
		x = 1;
	else if (check_quotes(cmdline + i) == 2 || check_redirs(cmdline + i) == 2 || check_pipes(shell, cmdline + i) == 2)
		x = 2;
	if (x > 0)
	{
		if (x == 2)
			printf("Syntax error!\n");
		if (shell->input->line != NULL)
		{
			free (shell->input->line);
			shell->input->line = NULL;
		}
		return (x);
	}
	return (0);
}
