/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_builtins.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 15:49:28 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/12 15:57:52 by wsonepou      ########   odam.nl         */
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

pid_t	builtin_child_exec(t_shell *shell, t_ctable *tmp, int node_nr)
{
	int	pid;

	if (shell->input->node_count == 1)
	{
		builtin_execute(shell, tmp);
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		if (handling_redirs(shell, tmp, node_nr) == false)
			kill_program(shell, NULL, errno);
		builtin_execute(shell, tmp);
		kill_program(shell, NULL, EXIT_SUCCESS);
	}
	if (dup2(shell->input->fds[0], STDIN_FILENO) == -1)
		kill_program(shell, "child dup2 fds[0]", errno);
	closing_fds(shell);
	return (pid);
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