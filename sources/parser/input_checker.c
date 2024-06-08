/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_checker.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 16:35:52 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/07 18:31:55 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_symbol(char *input)
{
	int	i;

	i = 1;
	while (ft_is_whitespace(input[i]))
		i++;
	if (input[i] == '\0' || input[i] == '|' || input[i] == '<' || input[i] == '>')
		return (1);
	return (0);
}

static int	check_quotes(char *input, char c)
{
	int	i;

	i = 1;
	while (input[i] != c && input[i] != '\0')
		i++;
	if (input[i] == c)
		return (i);
	return (0);
}

static int	string_check(char *input)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			o = check_quotes(input + i, input[i]);
			if (o == 0)
				return (1);
			i += o;
			o = 0;
		}
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i + 1] == '<'))
				i++;
			if (check_symbol(input + i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

// Checks the input, but will need to be changed for quotes to work like bash
int	input_checker(char **input)
{
	int	i;
	int	x;

	i = 0;
	while (ft_is_whitespace(*input[i]))
		i++;
	if (*input[i] == '\0')
		x = 2;
	else
		x = string_check(*input);
	if (x > 0)
	{
		if (x == 1)
			printf("Syntax error!\n");
		free (*input);
		return (1);
	}
	return (0);
}
