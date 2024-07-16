/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 12:11:12 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/16 11:13:45 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_flag(char *str)
{
	int	i;

	if (str[0] != '-')
		return (false);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (false);
		if (str[i] == 'n')
			i++;
	}
	return (true);
}

int	ft_mini_echo(t_shell *shell, char **split_input)
{
	int		i;
	int		j;
	bool	newline;

	i = 1;
	newline = true;
	if (shell->env_list == NULL)
		return (0);
	if (split_input[1] != NULL && ft_check_flag(split_input[1]) != 0)
	{
		j = 2;
		while (split_input[j] != NULL && ft_check_flag(split_input[j]) != 0)
			j++;
		newline = false;
		i = j;
	}
	while (split_input[i] != NULL)
	{
		ft_putstr_fd(split_input[i++], STDOUT_FILENO);
		if (split_input[i] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
