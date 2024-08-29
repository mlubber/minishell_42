/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_builtins.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 15:49:28 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/29 17:11:28 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_execute(t_shell *shell, t_ctable *tmp, bool child)
{
	if (ft_strncmp(tmp->cmd_array[0], "echo", 5) == 0)
		ft_mini_echo(shell, tmp->cmd_array);
	else if (ft_strncmp(tmp->cmd_array[0], "cd", 3) == 0)
		ft_mini_cd(shell, tmp->cmd_array);
	else if (ft_strncmp(tmp->cmd_array[0], "pwd", 4) == 0)
		ft_mini_pwd(shell);
	else if (ft_strncmp(tmp->cmd_array[0], "export", 7) == 0)
		ft_mini_export(shell, tmp->cmd_array);
	else if (ft_strncmp(tmp->cmd_array[0], "unset", 6) == 0)
		ft_mini_unset(shell, tmp->cmd_array);
	else if (ft_strncmp(tmp->cmd_array[0], "env", 4) == 0)
		ft_mini_env(shell, tmp->cmd_array);
	else if (ft_strncmp(tmp->cmd_array[0], "exit", 5) == 0)
		ft_mini_exit(shell, tmp->cmd_array);
	if (child == true)
		kill_program(shell, NULL, EXIT_SUCCESS);
	return (-1);
}

pid_t	builtin_child_exec(t_shell *shell, t_ctable *tmp, int node_nr)
{
	char	*file;

	if (shell->input->node_count == 1)
	{
		file = handling_redirs(shell, tmp, node_nr, 1);
		if (file != NULL)
		{
			handle_error(file, errno);
			return (-1);
		}
		return (builtin_execute(shell, tmp, false));
	}
	shell->pid = fork();
	if (shell->pid == -1)
		kill_program(shell, NULL, errno);
	if (shell->pid == 0)
	{
		file = handling_redirs(shell, tmp, node_nr, 1);
		if (file != NULL)
			kill_program(shell, file, errno);
		builtin_execute(shell, tmp, true);
	}
	if (shell->input->fds[0] != -1 && dup2(shell->input->fds[0], 0) == -1)
		kill_program(shell, "child dup2 fds[0]", errno);
	return (shell->pid);
}

int	builtin_check(t_ctable *tmp)
{
	int	x;

	x = 0;
	if (tmp->cmd_array == NULL)
	{
		return (0);
	}
	if (ft_strncmp(tmp->cmd_array[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(tmp->cmd_array[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(tmp->cmd_array[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(tmp->cmd_array[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(tmp->cmd_array[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(tmp->cmd_array[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(tmp->cmd_array[0], "exit", 5) == 0)
		return (1);
	return (0);
}
