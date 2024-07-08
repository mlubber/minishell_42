/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 12:11:12 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/08 15:52:48 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_mini_echo(t_shell *shell, char **split_input)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (shell->env_list == NULL)
		return (0);
	if (split_input[1] != NULL && ft_strncmp(split_input[1], "-n", 2) == 0)
	{
		newline = false;
		i = 2;
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
