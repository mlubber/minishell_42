/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 12:38:42 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/27 14:59:21 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_for_children(t_shell *shell, pid_t pid)
{
	int		status;
	pid_t	wpid;

	wpid = waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
	if (WIFSIGNALED(status))
	{
		if (g_signal == 2)
			shell->exit_code = 130;
		else
			shell->exit_code = status;
	}
	else if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		shell->exit_code = status;
	}
	else if (status == 0)
		shell->exit_code = 0;
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
	init_signals(shell, 2);
	if (cmd_path == NULL && access(cmds[0], F_OK | X_OK) == -1)
	{
		free(cmd_path);
		cmd_not_found(shell, cmds);
	}
	else if (paths == NULL)
		execute_cmd(shell, cmds[0], cmds, envp);
	else if (cmd_path != NULL)
		execute_cmd(shell, cmd_path, cmds, envp);
	ft_free_arr(&paths);
	free(envp);
	cmd_not_found(shell, cmds);
}

static void	run_child(t_shell *shell, t_ctable *tmp, char **paths, int node_nr)
{
	char	**envp;
	char	*file;

	file = handling_redirs(shell, tmp, node_nr);
	if (file != NULL || tmp->cmd_array == NULL)
		kill_program(shell, file, errno);
	envp = ft_create_env(shell);
	if (ft_strnstr(tmp->cmd_array[0], "/", ft_strlen(tmp->cmd_array[0])))
	{
		execute_cmd(shell, tmp->cmd_array[0], tmp->cmd_array, envp);
		ft_free_arr(&paths);
		free(envp);
		check_if_dir(shell, tmp->cmd_array);
	}
	else
		create_cmd_path(shell, tmp->cmd_array, paths, envp);
}

static pid_t	checking_cmd(t_shell *shell, t_ctable *cnode, int node_nr)
{
	char	**paths;

	paths = NULL;
	if (builtin_check(cnode) == 1)
		return (builtin_child_exec(shell, cnode, node_nr));
	g_signal = -1;
	paths = ft_get_paths(shell);
	shell->pid = fork();
	if (shell->pid == -1)
		kill_program(shell, NULL, errno);
	if (shell->pid == 0)
		run_child(shell, cnode, paths, node_nr);
	if (shell->input->fds[0] != -1 && dup2(shell->input->fds[0], 0) == -1)
		kill_program(shell, "exec_cmd child dup2 fds[0]", errno);
	ft_free_arr(&paths);
	return (shell->pid);
}

void	start_execution(t_shell *shell, int i)
{
	pid_t		pid;
	t_ctable	*tmp;

	tmp = shell->input->cnode;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
			if (pipe(shell->input->fds) == -1)
				kill_program(shell, "Failed pipe multiple cmds", errno);
		pid = checking_cmd(shell, tmp, i);
		closing_fds(shell);
		i++;
		tmp = tmp->next;
		if (tmp == NULL)
			if (dup2(shell->stdinput, STDIN_FILENO) == -1)
				kill_program(shell, "Failed resetting stdin", errno);
	}
	if (pid != -1)
		wait_for_children(shell, pid);
}
