/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/29 17:17:55 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	pre_exec_check(t_shell *shell, int i)
{
	char	*file;

	if (check_heredoc(shell) == 130)
	{
		shell->exit_code = 130;
		return (0);
	}
	if (shell->input->cnode->cmd_array == NULL)
	{
		file = handling_redirs(shell, shell->input->cnode, i, 0);
		if (file != NULL)
		{
			handle_error(file, errno);
			if (errno == 21)
				shell->exit_code = 1;
			else
				shell->exit_code = errno;
		}
		return (0);
	}
	return (1);
}

static void	reset_input_values(t_shell *shell, t_input *input)
{
	init_signals(shell, 1);
	input->var_len = 0;
	input->var_val_len = 0;
	input->word_len = 0;
	input->cmd_seg = 0;
	input->node_count = 0;
	input->cnode = NULL;
	if (dup2(shell->stdinput, STDIN_FILENO) == -1)
		kill_program(shell, "Failed resetting stdin", errno);
	if (dup2(shell->stdoutput, STDOUT_FILENO) == -1)
		kill_program(shell, "Failed resetting stdout", errno);
	g_signal = 0;
}

void	ft_minishell_loop(t_shell *shell)
{
	while (1)
	{
		reset_input_values(shell, shell->input);
		shell->input->line = readline("minishell: ");
		if (g_signal == 2)
			shell->exit_code = 130;
		if (shell->input->line == NULL)
			kill_program(shell, NULL, shell->exit_code);
		else if (shell->input->line[0] == '\0')
		{
			free (shell->input->line);
			continue ;
		}
		add_history(shell->input->line);
		if (input_checker(shell, shell->input->line) > 0)
			continue ;
		create_ctable(shell, shell->input->line);
		free (shell->input->line);
		if (pre_exec_check(shell, 0) == 1)
			start_execution(shell, 0);
		free_cmd_list(&shell->input->cnode);
	}
}
