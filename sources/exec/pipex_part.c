/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_part.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:50:25 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/04 17:01:26 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	exec_cmd(t_shell *shell, t_ctable *cnode)
// {
// 	int		i;
// 	char	*cmd_path;

// 	i = 0;
// 	cmd_path = ft_pathjoin(shell->paths[i], cnode->cmd_array[0]);
// 	while (cmd_path != NULL && access(cmd_path, F_OK | X_OK) == -1)
// 	{
// 		free(cmd_path);
// 		cmd_path = ft_pathjoin(shell->paths[i++], cnode->cmd_array[0]);
// 	}
// 	if (cmd_path == NULL && access(cnode->cmd_array[0], F_OK | X_OK) == -1)
// 	{
// 		free_command(cmds, &cmd_path);
// 		kill_program(shell, cmd, 127);
// 	}
// 	else
// 		execve(cmd_path, cnode->cmd_array, envp);
// 	kill_program(shell, cnode->cmd_array[0], errno);
// }

// static pid_t	last_child(t_shell *shell)
// {
// 	const pid_t	pid = fork();
// 	int			outfile;

// 	if (pid == -1)
// 		kill_program(shell, "last child fork", errno);
// 	if (pid == 0)
// 	{
// 		if (dup2(outfile, STDOUT_FILENO) == -1)
// 			kill_program(shell, "last child dup2 outfile", errno);
// 		if (close(outfile) == -1)
// 			perror("outfile");
// 		exec_cmd(shell, argv, envp);
// 	}
// 	close(STDIN_FILENO);
// 	return (pid);
// }

// static void	child(t_shell *shell)
// {
// 	const pid_t	pid = fork();

// 	if (pid == -1)
// 		kill_program(shell, "child fork", errno);
// 	if (pid == 0)
// 	{
// 		setting_io(shell);
// 		exec_cmd(shell);
// 	}
// 	if (dup2(shell->input->fds[0], STDIN_FILENO) == -1)
// 		kill_program(shell, "child dup2 fds[0]", errno);
// 	closing_fds(shell->input->fds);
// }


// pid_t	creating_children(t_shell *shell, t_ctable *cnode)
// {
// 	int		i;
// 	pid_t	pid;

// 	i = 0;
// 	while (i < shell->input->cmds_count)
// 	{
// 		if (pipe(shell->input->fds) == -1)
// 			kill_program(shell, "Error: failed creating pipe", 8);
// 		child(shell);
// 		i++;
// 	}
// 	pid = last_child(shell);
// 	closing_fds(shell->input->fds);
// 	return (pid);
// }