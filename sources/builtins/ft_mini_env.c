/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_envp.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/27 12:11:48 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_mini_env(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->envp[i])
	{
		ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
