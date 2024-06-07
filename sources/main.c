/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/21 09:23:10 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/07 14:58:38 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_shell(t_shell *shell)
{
	shell->input = NULL;
	shell->paths = NULL;
	shell->envp = NULL;
	shell->pwd = NULL;
	shell->old_pwd = NULL;
	shell->env_size = 0;
	shell->env_list = NULL;
	shell->lexer_list = NULL;
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1 || argv[1])
		kill_program(&shell, "Program does not take arguments >:(\n", 1);
	init_shell(&shell);
	building_env(&shell, &shell.env_list, envp);
	ft_minishell_loop(&shell);
	kill_program(&shell, NULL, EXIT_SUCCESS);
	return (0);
}

