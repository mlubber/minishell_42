/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 12:38:42 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/13 14:20:32 by wsonepou      ########   odam.nl         */
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

static pid_t	exec_cmd(t_shell *shell, t_ctable *tmp, char **paths, int node_nr)
{
	char	**envp;
	char	*file;
	pid_t	pid;

	if (builtin_check(tmp) == 1)
		return (builtin_child_exec(shell, tmp, node_nr));
	pid = fork();
	if (pid == -1)
		kill_program(shell, NULL, errno);
	if (pid == 0)
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
	return (pid);
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
				kill_program(shell, "Failed resetting stdin", 7);
	}
	while (wait(NULL) != -1)
		continue ;
}

