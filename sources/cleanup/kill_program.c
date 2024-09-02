/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kill_program.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 14:08:00 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/09/02 13:33:41 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	closing_fds(t_shell *shell)
{
	if (shell->input->fds[0] != -1 && close(shell->input->fds[0]) == -1)
		perror("shell->input->fds[0]");
	if (shell->input->fds[1] != -1 && close(shell->input->fds[1]) == -1)
		perror("shell->input->fds[1]");
	shell->input->fds[0] = -1;
	shell->input->fds[1] = -1;
}

// Frees all nodes
void	free_env_node(t_env **node)
{
	if ((*node)->str != NULL)
		free((*node)->str);
	if ((*node)->var_name != NULL)
		free((*node)->var_name);
	if ((*node)->var_val != NULL)
		free((*node)->var_val);
	free(*node);
}

// Frees our malloced environment
static void	free_env(t_shell *shell, t_env **env_head)
{
	t_env	*tmp;

	tmp = *env_head;
	while (env_head != NULL && tmp != NULL)
	{
		tmp = tmp->next;
		if (*env_head != NULL)
			free_env_node(env_head);
		*env_head = tmp;
	}
	if (shell->pwd != NULL)
		free (shell->pwd);
	if (shell->old_pwd != NULL)
		free (shell->old_pwd);
	if (shell->home != NULL)
		free (shell->home);
}

// Cleans up all malloced stuff and exits minishell
void	kill_program(t_shell *shell, char *msg, int exit_code)
{
	free_env(shell, &shell->env_list);
	if (shell->stdinput != -1 && close(shell->stdinput) == -1)
		perror("Failed closing shell->stdinput");
	if (shell->stdoutput != -1 && close(shell->stdoutput) == -1)
		perror("Failed closing shell->stdoutput");
	closing_fds(shell);
	rl_clear_history();
	if (exit_code > 0)
	{
		handle_error(msg, exit_code);
		if (shell->input->cnode != NULL)
			free_cmd_list(&shell->input->cnode);
		exit(exit_code);
	}
	else if (msg != NULL && exit_code == 0)
		write(2, msg, ft_strlen(msg));
	if (shell->input->cnode != NULL)
		free_cmd_list(&shell->input->cnode);
	exit(EXIT_SUCCESS);
}
