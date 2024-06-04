/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 16:32:04 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_mini_pwd(t_tools *tools)
{
	ft_putendl_fd(tools->pwd, STDOUT_FILENO);
}
