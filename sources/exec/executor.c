/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 12:38:42 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/19 16:51:44 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	remove_child_pid(t_shell *shell, pid_t pid)
// {
// 	int	i;

// 	i = 0;
// 	while (i < shell->input->node_count)
// 	{
// 		if (shell->input->pids[i] == pid)
// 			shell->input->pids[i] = -1;
// 		i++;
// 	}
// }

void	signal_received(t_shell *shell, pid_t *pids, int node_count, int status)
{
	int	i;
	
	// printf("termsig 1: %d\n", status);
	status = WTERMSIG(status);
	// printf("termsig 2: %d\n", status);
	if (g_signal)
	{
		g_signal = 0;
		i = 0;
		while (i < node_count)
		{
			if (pids[i] != -1)
				kill(pids[i], SIGINT);
			// printf("\nsignaled pid: %d", pids[i]);
			i++;
		}
		// printf("\n");
	}
	shell->exit_code = status;
}

void	wait_for_children(t_shell *shell, pid_t *pids, int node_count)
{
	int	status;
	int	i;
	// int	j;
	int	pid;

	i = 0;
	while (i < node_count)
	{
		// printf("status 1: %d\n", status);
		pid = waitpid(pids[i], &status, 0);
		// printf("pid = %d\n", pid);
		// printf("\n\n%d\n\n", WIFSIGNALED(status));
		// remove_child_pid(shell, pid);
		// printf("status 2: %d\n", status);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			shell->exit_code = status;
		}
		else if (status == 0)
		{
			shell->exit_code = 0;
		}
		if (WIFSIGNALED(status))
		{
			signal_received(shell, pids, node_count, status);
		}
		i++;
	}
	// i = 0;
	// while (i < shell->input->node_count)
	// {
	// 	printf("remaining pid #%d: %d\n", i, shell->input->pids[i]);
	// 	i++;
	// }
}

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
		kill_program(shell, NULL, 126);
	}
	else
		execve(cmd_path, cmds, envp);
	ft_not_found_free(cmds, paths, envp);
	kill_program(shell, NULL, errno);
}

static pid_t	exec_cmd(t_shell *shell, t_ctable *tmp, char **paths, int node_nr)
{
	char	**envp;
	char	*file;
	// pid_t	pid;

	if (builtin_check(tmp) == 1)
		return (builtin_child_exec(shell, tmp, node_nr));
	shell->pid = fork();
	if (shell->pid == -1)
		kill_program(shell, NULL, errno);
	if (shell->pid == 0)
	{
		file = handling_redirs(shell, tmp, node_nr);
		if (file != NULL || tmp->cmd_array == NULL)
			kill_program(shell, file, errno);
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
	if (shell->input->fds[0] != -1 && dup2(shell->input->fds[0], STDIN_FILENO) == -1)
		kill_program(shell, "exec_cmd child dup2 fds[0]", errno);
	closing_fds(shell);
	return (shell->pid);
}

static pid_t	executing_one_cmd(t_shell *shell, t_ctable *tmp, int node_nr)
{
	char	**paths;
	pid_t	pid;

	paths = ft_get_paths(shell);
	pid = exec_cmd(shell, tmp, paths, node_nr);
	ft_free_arr(&paths);
	return (pid);
}

void	start_execution(t_shell *shell)
{
	int			i;
	t_ctable	*tmp;

	i = 0;
	tmp = shell->input->cnode;
	if (check_heredoc(shell) == 130)
		return ;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			if (pipe(shell->input->fds) == -1)
			{
				perror("pipe");
				kill_program(shell, "Failed pipe multiple cmds", errno);
			}
		}
		shell->input->pids[i] = executing_one_cmd(shell, tmp, i);
		i++;
		tmp = tmp->next;
		if (tmp == NULL)
			if (dup2(shell->stdinput, STDIN_FILENO) == -1)
				kill_program(shell, "Failed resetting stdin", errno);
	}
	if (shell->input->pids[i - 1] != -1) // NOT THE SOLUTION FOR A SINGLE BUILTIN
		wait_for_children(shell, shell->input->pids, shell->input->node_count);
}

