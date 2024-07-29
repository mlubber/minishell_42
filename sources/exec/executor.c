/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 12:38:42 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/29 13:57:06 by link          ########   odam.nl         */
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

static void	exec_cmd(t_shell *shell, t_ctable *tmp, char **paths, int *pipe_fd)
{
	char	**envp;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		if (tmp->next)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
		}
		dup2(shell->stdinput, STDIN_FILENO);
		envp = ft_create_env(shell);
		if (ft_strnstr(tmp->cmd_array[0], "/", ft_strlen(tmp->cmd_array[0])))
		{
			execve(tmp->cmd_array[0], tmp->cmd_array, envp);
			ft_not_found_free(tmp->cmd_array, paths, envp);
			kill_program(shell, NULL, errno);
		}
		else
			create_cmd_path(shell, tmp->cmd_array, paths, envp);
	}
	else if (pid > 0)
	{
		wait(NULL);
		if (tmp->next)
		{
			close(pipe_fd[1]);
			shell->stdinput = pipe_fd[0];
		}
	}
	else
		wait(NULL);
}

static void	executing_one_cmd(t_shell *shell, t_ctable *tmp, int *pipe_fd)
{
	bool	open_success;
	char	**paths;

	open_success = handling_redirs(shell, tmp);
	if (open_success == false)
		return ;
	if (builtin_check(shell) == 1)
		return ;
	paths = ft_get_paths(shell);
	exec_cmd(shell, tmp, paths, pipe_fd);
	ft_free_arr(&paths);
}

void	start_execution(t_shell *shell)
{
	int			pipe_fd[2];
	t_ctable	*tmp;

	tmp = shell->input->cnode;
	while (tmp != NULL)
	{
		if (tmp->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("minishell");
				kill_program(shell, "Failed pipe multiple cmds", errno);
			}
		}
		executing_one_cmd(shell, tmp, pipe_fd);
		tmp = tmp->next;
	}
}

// void	start_execution(t_shell *shell)
// {
// 	int		pipe_fd[2];

// 	// if (shell->input->cmds_count == 1)
// 	// 	executing_one_cmd(shell, shell->input->cnode, pipe_fd);
// 	// else
// 	executing_multiple_cmds(shell, pipe_fd);
// }
