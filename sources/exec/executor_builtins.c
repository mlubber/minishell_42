/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_builtins.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 15:49:28 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/30 16:05:04 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_execute(t_shell *shell, t_ctable *tmp)
{
	if (ft_strncmp(tmp->cmd_array[0], "echo", 5) == 0)
		return (ft_mini_echo(shell, tmp->cmd_array));
	else if (ft_strncmp(tmp->cmd_array[0], "cd", 3) == 0)
		return (ft_mini_cd(shell, tmp->cmd_array));
	else if (ft_strncmp(tmp->cmd_array[0], "pwd", 4) == 0)
		return (ft_mini_pwd(shell));
	else if (ft_strncmp(tmp->cmd_array[0], "export", 7) == 0)
		return (ft_mini_export(shell, tmp->cmd_array));
	else if (ft_strncmp(tmp->cmd_array[0], "unset", 6) == 0)
		return (ft_mini_unset(shell, tmp->cmd_array));
	else if (ft_strncmp(tmp->cmd_array[0], "env", 4) == 0)
		return (ft_mini_env(shell, tmp->cmd_array));
	else if (ft_strncmp(tmp->cmd_array[0], "exit", 5) == 0)
		return (ft_mini_exit(shell, tmp->cmd_array));
	return (0);
}

void	builtin_child_exec(t_shell *shell, t_ctable *tmp, int *pipe_fd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (tmp->next)
		{
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				kill_program(shell, "Child stdout dup fail", errno);
		}
		if (dup2(shell->stdinput, STDIN_FILENO) == -1)
			kill_program(shell, "Child stdin dup fail", errno);
		handling_redirs(shell, tmp);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		builtin_execute(shell, tmp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, NULL, 0);
		shell->stdinput = STDIN_FILENO;
		if (tmp->next)
		{
			close(pipe_fd[1]);
			shell->stdinput = pipe_fd[0];
		}
	}
}

int	builtin_check(t_ctable *tmp)
{
	int	x;

	x = 0;
	if (tmp->cmd_array == NULL)
		return (0);
	if (ft_strncmp(tmp->cmd_array[0], "echo", 5) == 0)
		x = 1;
	else if (ft_strncmp(tmp->cmd_array[0], "cd", 3) == 0)
		x = 1;
	else if (ft_strncmp(tmp->cmd_array[0], "pwd", 4) == 0)
		x = 1;
	else if (ft_strncmp(tmp->cmd_array[0], "export", 7) == 0)
		x = 1;
	else if (ft_strncmp(tmp->cmd_array[0], "unset", 6) == 0)
		x = 1;
	else if (ft_strncmp(tmp->cmd_array[0], "env", 4) == 0)
		x = 1;
	else if (ft_strncmp(tmp->cmd_array[0], "exit", 5) == 0)
		x = 1;
	if (x == 1)
		return (1);
	return (0);
}

// int	builtin_check(t_shell *shell, t_ctable *tmp)
// {
// 	int	x;

// 	x = 0;
// 	if (tmp->cmd_array == NULL)
// 		return (0);
// 	if (ft_strncmp(tmp->cmd_array[0], "echo", 5) == 0)
// 		x = ft_mini_echo(shell, tmp->cmd_array);
// 	else if (ft_strncmp(tmp->cmd_array[0], "cd", 3) == 0)
// 		x = ft_mini_cd(shell, tmp->cmd_array);
// 	else if (ft_strncmp(tmp->cmd_array[0], "pwd", 4) == 0)
// 		x = ft_mini_pwd(shell);
// 	else if (ft_strncmp(tmp->cmd_array[0], "export", 7) == 0)
// 		x = ft_mini_export(shell, tmp->cmd_array);
// 	else if (ft_strncmp(tmp->cmd_array[0], "unset", 6) == 0)
// 		x = ft_mini_unset(shell, tmp->cmd_array);
// 	else if (ft_strncmp(tmp->cmd_array[0], "env", 4) == 0)
// 		x = ft_mini_env(shell, tmp->cmd_array);
// 	else if (ft_strncmp(tmp->cmd_array[0], "exit", 5) == 0)
// 		x = ft_mini_exit(shell, tmp->cmd_array);
// 	if (x == 1)
// 		return (1);
// 	return (0);
// }