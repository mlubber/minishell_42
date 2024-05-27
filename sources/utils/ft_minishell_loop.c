/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/27 09:30:37 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	minishell_loop(t_tools *tools)
{
	char	*temp;

	tools->args = readline("minishell: ");
	temp = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = temp;
	printf("%s\n", tools->args);
	free(temp);
	return (1);
}
