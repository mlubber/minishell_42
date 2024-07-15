/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 12:38:42 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/15 17:13:14 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cmd_not_found(char **cmd)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	ft_putstr_fd(": command not found\n", 2);
	ft_free_arr(&cmd);
	exit(127);
}

char	**ft_get_paths(t_shell *shell)
{
	char	*paths;
	char	**split_paths;
	t_env	*tmp;

	tmp = shell->env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, "PATH", 5) == 0)
		{
			paths = tmp->var_val;
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (NULL);
	split_paths = ft_split(paths, ':');
	if (split_paths == NULL)
		kill_program(shell, "failed mallocing split_paths", 6);
	return (split_paths);
}

char	*ft_connectstring(char const *s1, char const *s2, char c)
{
	int		i;
	int		o;
	char	*p;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	o = ft_strlen(s1) + ft_strlen(s2);
	p = malloc((o + 2) * sizeof(char));
	if (!p)
		return (NULL);
	while (*s1)
		p[i++] = *s1++;
	p[i] = c;
	i++;
	while (*s2)
		p[i++] = *s2++;
	p[i] = '\0';
	return (p);
}

static void	exec_cmd(t_shell *shell, char **cmds, char **paths)
{
	int		i;
	char	*cmd_path = NULL;
	char	**envp;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		i = 0;
		envp = ft_create_export_list(shell, shell->env_list, 0);
		if (paths != NULL)
			cmd_path = ft_connectstring(paths[i], cmds[0], '/');
		while (cmd_path != NULL && access(cmd_path, F_OK | X_OK) == -1)
		{
			free(cmd_path);
			cmd_path = ft_connectstring(paths[i++], cmds[0], '/');
		}
		if (cmd_path == NULL && access(cmds[0], F_OK | X_OK) == -1)
		{
			ft_free_arr(&paths);
			ft_free_arr(&envp);
			free(cmd_path);
			ft_cmd_not_found(cmds);
			kill_program(shell, NULL, 127);
		}
		else
			execve(cmd_path, cmds, envp);
		ft_free_arr(&paths);
		ft_free_arr(&envp);
		ft_cmd_not_found(cmds);
		kill_program(shell, NULL, errno);
	}
	else
		wait(NULL);
}

// static char	**ft_get_paths(char **envp)
// {
// 	char	**paths;
// 	int		i;
// 	int		j;

// 	j = 0;
// 	while (envp[j] != NULL)
// 		j++;
// 	i = 0;
// 	while (i < j && (ft_strnstr(envp[i], "PATH", 4) == NULL))
// 		i++;
// 	if (i >= j)
// 		exit(EXIT_FAILURE);
// 	paths = ft_split(envp[i] + 5, ':');
// 	return (paths);
// }

// char	*ft_get_exec_cmd(char *cmd, char **envp)
// {
// 	char	**dir_list;
// 	char	*full_dir_path;
// 	char	*exec_cmd;
// 	int		i;

// 	i = 0;
// 	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
// 		return (cmd);
// 	dir_list = ft_get_paths(envp);
// 	if (dir_list == NULL)
// 		return (NULL);
// 	i = -1;
// 	while (dir_list[++i])
// 	{
// 		full_dir_path = ft_strjoin(dir_list[i], "/");
// 		exec_cmd = ft_strjoin(full_dir_path, cmd);
// 		free(full_dir_path);
// 		if (access(exec_cmd, F_OK | X_OK) == 0)
// 		{
// 			ft_free_list(dir_list);
// 			return (exec_cmd);
// 		}
// 		free(exec_cmd);
// 	}
// 	ft_free_list(dir_list);
// 	return (NULL);
// }

// static void execute_cmd(t_shell *shell, t_ctable *cnode)
// {
// 	char	**envp_array;
// 	t_env	*temp;
// 	int		i;
// 	int		env_size;
// 	int		pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		i = 0;
// 		temp = shell->env_list;
// 		while (temp != NULL)
// 		{
// 			// printf("env: %s\n", temp->str);
// 			i++;
// 			temp = temp->next;
// 		}
// 		env_size = i;
// 		envp_array = malloc((env_size + 1) * sizeof(char *));
// 		i = 0;
// 		temp = shell->env_list;
// 		while (i < env_size)
// 		{
// 			envp_array[i] = temp->str;
// 			// printf("env_array: %s\n", envp_array[i]);
// 			temp = temp->next;
// 			i++;
// 		}
// 		envp_array[i] = NULL;
// 		if (cnode->cmd_array[0] && ft_get_exec_cmd(cnode->cmd_array[0], envp_array))
// 			execve(ft_get_exec_cmd(cnode->cmd_array[0], envp_array), cnode->cmd_array, envp_array);
// 		ft_cmd_not_found(cnode->cmd_array);
// 	}
// 	else
// 		wait(NULL);
// }

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
	char	**paths;

	open_success = handling_redirs(shell, shell->input->cnode);
	if (open_success == false)
		return ;
	if (builtin_check(shell) == 1)
		return ;
	paths = ft_get_paths(shell);
	exec_cmd(shell, shell->input->cnode->cmd_array, paths);
	ft_free_arr(&paths);
	// execute_cmd(shell, shell->input->cnode);
}

void	start_execution(t_shell *shell)
{
	if (shell->input->cmds_count == 1)
		executing_one_cmd(shell);
	else
		executing_multiple_cmds(shell);
}

