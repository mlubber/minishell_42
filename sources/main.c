/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/21 09:23:10 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/27 13:48:01 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal = 0;

// Initializing shell struct
static void	init_shell(t_shell *shell)
{
	init_signals(shell, 1);
	shell->pwd = NULL;
	shell->old_pwd = NULL;
	shell->env_size = 0;
	shell->env_list = NULL;
	shell->exit_code = 0;
	shell->pid = 1;
	shell->stdinput = dup(STDIN_FILENO);
	if (shell->stdinput == -1)
		kill_program(shell, "Failed to dup STDIN", errno);
	shell->stdoutput = dup(STDOUT_FILENO);
	if (shell->stdoutput == -1)
		kill_program(shell, "Failed to dup STDOUT", errno);
	shell->input->fds[0] = -1;
	shell->input->fds[1] = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_input	input;

	if (argc != 1 || argv[1])
		exit(1);
	shell.input = &input;
	init_shell(&shell);
	building_env(&shell, &shell.env_list, envp);
	ft_minishell_loop(&shell);
	kill_program(&shell, NULL, EXIT_SUCCESS);
	return (0);
}
