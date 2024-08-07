/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/21 09:23:10 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/05 14:49:22 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Initializing shell struct
static void	init_shell(t_shell *shell)
{
	shell->pwd = NULL;
	shell->old_pwd = NULL;
	shell->env_size = 0;
	shell->env_list = NULL;
	shell->exit_code = 0;
	shell->stdinput = dup(STDIN_FILENO);
	shell->stdoutput = dup(STDOUT_FILENO);
	init_signals();
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_input	input;

	shell.input = &input;
	init_shell(&shell);
	building_env(&shell, &shell.env_list, envp);
	// if (argc != 1 || argv[1])
	// 	kill_program(&shell, "Program does not take arguments >:(\n", 1);
	ft_minishell_loop(&shell, argc, argv);
	kill_program(&shell, NULL, EXIT_SUCCESS);
	return (0);
}

