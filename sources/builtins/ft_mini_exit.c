/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 11:27:19 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/08 15:53:07 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Doesn't work
int	ft_mini_exit(t_shell *shell, char **cmds)
{
	if (cmds[1] != NULL)
	{
		printf("Exit does not take arguments!\n");
		return (1);
	}
	kill_program(shell, "exit", 0);
	return (1);
}
