/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 12:11:12 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/07 15:04:43 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_mini_echo(t_shell *shell, char **split_input)
{
	printf("Echo is still getting build!");
	if (split_input != NULL)		//
		return (1);					// Placement holder to make code work
	if (shell->env_list != NULL)	//
		return (1);					//
	return (1);
}