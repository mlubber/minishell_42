/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/09 10:37:27 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_mini_pwd(t_shell *shell, char **cmds)
{
	if (cmds[1] != NULL)
		ft_putendl_fd("pwd: Too many arguments", STDOUT_FILENO);
	else
		ft_putendl_fd(shell->pwd, STDOUT_FILENO);
	return (1);
}

