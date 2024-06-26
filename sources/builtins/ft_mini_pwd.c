/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/07 12:34:27 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Works fine
// *** split_input gets replaced by the command table linked list ***
int	ft_mini_pwd(t_shell *shell, char **split_input)
{
	if (split_input[1] != NULL)
		printf("pwd: Too many arguments");
	else
		ft_putendl_fd(shell->pwd, STDOUT_FILENO);
	return (1);
}
