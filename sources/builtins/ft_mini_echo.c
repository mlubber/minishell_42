/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 12:11:12 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/13 17:19:24 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// No work done yet
// *** split_input gets replaced by the command table linked list ***
int	ft_mini_echo(t_shell *shell, char **cmds)
{
	printf("Echo is still getting build!");
	if (cmds != NULL)		//
		return (1);					// Placement holder to make code work
	if (shell->env_list != NULL)	//
		return (1);					//
	return (1);
}