/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/21 09:23:10 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/13 16:48:11 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Initializing shell struct
static void	init_shell(t_shell *shell)
{
	shell->paths = NULL;
	shell->envp = NULL;
	shell->pwd = NULL;
	shell->old_pwd = NULL;
	shell->env_size = 0;
	shell->env_list = NULL;

	shell->input->cmds = NULL;
	shell->input->var_val = NULL;
	shell->input->var_val_len = 0;
	shell->input->var_len = 0;
	shell->input->cmd_len = 0;
	shell->input->part_len = 0;
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_input	input;

	if (argc != 1 || argv[1])
		kill_program(&shell, "Program does not take arguments >:(\n", 1);
	shell.input = &input;
	init_shell(&shell);
	building_env(&shell, &shell.env_list, envp);
	ft_minishell_loop(&shell);
	kill_program(&shell, NULL, EXIT_SUCCESS);
	return (0);
}

