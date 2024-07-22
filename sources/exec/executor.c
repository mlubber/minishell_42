/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 12:38:42 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/22 12:52:12 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_cmd_path(t_shell *shell, char **cmds, char **paths, char **envp)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	if (paths != NULL)
		cmd_path = ft_connectstring(paths[i], cmds[0], '/');
	while (cmd_path != NULL && access(cmd_path, F_OK | X_OK) == -1)
	{
		free(cmd_path);
		cmd_path = ft_connectstring(paths[i++], cmds[0], '/');
	}
	if (cmd_path == NULL && access(cmds[0], F_OK | X_OK) == -1)
	{
		free(cmd_path);
		ft_not_found_free(cmds, paths, envp);
		kill_program(shell, NULL, 127);
	}
	else
		execve(cmd_path, cmds, envp);
	ft_not_found_free(cmds, paths, envp);
	kill_program(shell, NULL, errno);
}

static void	exec_cmd(t_shell *shell, char **cmds, char **paths)
{
	int		i;
	char	*cmd_path;
	char	**envp;
	int		pid;

	cmd_path = NULL;
	pid = fork();
	if (pid == 0)
	{
		i = 0;
		envp = ft_create_env(shell);
		if (ft_strnstr(cmds[0], "/", ft_strlen(cmds[0])))
		{
			execve(cmds[0], cmds, envp);
			ft_not_found_free(cmds, paths, envp);
			kill_program(shell, NULL, errno);
		}
		else
			create_cmd_path(shell, cmds, paths, envp);
	}
	else
		wait(NULL);
}

static void	executing_multiple_cmds(t_shell *shell)
{
	int			i;
	t_ctable	*tmp;

	i = 0;
	tmp = shell->input->cnode;
	printf("multiple cmds\n");
	while (tmp != NULL)
	{
		tmp = tmp->next;
	}
}

static void	executing_one_cmd(t_shell *shell)
{
	bool	open_success;
	char	**paths;

	open_success = handling_redirs(shell, shell->input->cnode);
	if (open_success == false)
		return ;
	if (builtin_check(shell) == 1)
		return ;
	paths = ft_get_paths(shell);
	exec_cmd(shell, shell->input->cnode->cmd_array, paths);
	ft_free_arr(&paths);
}

void	start_execution(t_shell *shell)
{
	if (shell->input->cmds_count == 1)
		executing_one_cmd(shell);
	else
		executing_multiple_cmds(shell);
}
