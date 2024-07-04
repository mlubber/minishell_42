/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 12:38:42 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/04 16:59:41 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	executing_multiple_cmds(t_shell *shell)
{
	int			i;
	t_ctable	*tmp;

	i = 0;
	tmp = shell->input->cnode;
	while (tmp != NULL)
	{
		tmp = tmp->next;
	}

}

// This function gets called to check if a cmd is a builtin function
int	builtin_check(t_shell *shell)
{
	int	x;

	x = 0;
	if (shell->input->cnode->cmd_array == NULL)
		return (0);
	if (ft_strncmp(shell->input->cnode->cmd_array[0], "echo", 5) == 0)
		x = ft_mini_echo(shell, shell->input->cnode->cmd_array);
	else if (ft_strncmp(shell->input->cnode->cmd_array[0], "cd", 3) == 0)
		x = ft_mini_cd(shell, shell->input->cnode->cmd_array);
	else if (ft_strncmp(shell->input->cnode->cmd_array[0], "pwd", 4) == 0)
		x = ft_mini_pwd(shell, shell->input->cnode->cmd_array);
	else if (ft_strncmp(shell->input->cnode->cmd_array[0], "export", 7) == 0)
		x = ft_mini_export(shell, shell->input->cnode->cmd_array);
	else if (ft_strncmp(shell->input->cnode->cmd_array[0], "unset", 6) == 0)
		x = ft_mini_unset(shell, shell->input->cnode->cmd_array);
	else if (ft_strncmp(shell->input->cnode->cmd_array[0], "env", 4) == 0)
		x = ft_mini_env(shell, shell->input->cnode->cmd_array);
	else if (ft_strncmp(shell->input->cnode->cmd_array[0], "exit", 5) == 0)
		x = ft_mini_exit(shell, shell->input->cnode->cmd_array);
	if (x == 1)
		return (1);
	return (0);
}

static void	executing_one_cmd(t_shell *shell)
{
	bool	open_success;

	open_success = handling_redirs(shell, shell->input->cnode);
	if (open_success == false)
		return ;
	if (builtin_check(shell) == 1)
		return ;
	// execute_cmd(shell, shell->input->cnode);
}

void	start_execution(t_shell *shell)
{
	if (shell->input->cmds_count == 1)
		executing_one_cmd(shell);
	else
		executing_multiple_cmds(shell);
}

