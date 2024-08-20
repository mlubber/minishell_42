/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/20 10:07:48 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_mini_pwd(t_shell *shell)
{
	// if (cmds[1] != NULL)
	// 	ft_putendl_fd("pwd: Too many arguments", STDERR_FILENO);
	// else
	ft_putendl_fd(shell->pwd, STDOUT_FILENO);
}

