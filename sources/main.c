/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/21 09:23:10 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 16:34:26 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_tools(t_tools *tools)
{
	tools->full_string = NULL;
	tools->paths = NULL;
	tools->envp = NULL;
	tools->pwd = NULL;
	tools->old_pwd = NULL;
	tools->env_size = 0;
	tools->env_list = NULL;
	tools->lexer_list = NULL;
}


int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	if (argc != 1 || argv[1])
		kill_program(&tools, "Program does not take arguments >:(\n", 1);
	init_tools(&tools);
	building_env(&tools, &tools.env_list, envp);
	ft_minishell_loop(&tools);
	delete_list(&tools.env_list);
	return (0);
}

