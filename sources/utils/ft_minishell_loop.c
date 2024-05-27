/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/27 13:48:02 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_reset_tools(t_tools *tools)
{
	// free(tools->args);
	ft_minishell_loop(tools);
	return (1);
}

int	ft_minishell_loop(t_tools *tools)
{
	char	*temp;

	tools->args = readline("minishell: ");
	temp = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = temp;
	if (tools->args[0] == '\0')
		return (ft_reset_tools(tools));
	else if (ft_strncmp(tools->args, "env", ft_strlen(tools->args)) == 0)
		ft_mini_env(tools);
	else if (ft_strncmp(tools->args, "pwd", ft_strlen(tools->args)) == 0)
		ft_mini_pwd(tools);
	else
		printf("%s\n", tools->args);
	ft_reset_tools(tools);
	free(temp);
	return (1);
}
