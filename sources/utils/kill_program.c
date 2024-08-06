/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kill_program.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 14:08:00 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/06 17:14:34 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	closing_fds(int *fds)
{
	if (fds[0] != -1 && close(fds[0]) == -1)
		perror("fds[0]");
	if (fds[1] != -1 && close(fds[1]) == -1)
		perror("fds[1]");
	fds[0] = -1;
	fds[1] = -1;
}

// Frees every node
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
void	free_env(t_shell *shell, t_env **env_head)
{
	t_env	*tmp;

	tmp = *env_head;
	while (env_head != NULL && tmp != NULL) // Freeing ENV linked list
	{
		tmp = tmp->next;
		if (*env_head != NULL)
			free_env_node(env_head);
		*env_head = tmp;
	}
	if (shell->pwd != NULL) // Freeing PWD   ------ Wijzen env PWD en shell->pwd naar zelfde malloc of verschillende?
		free (shell->pwd);
	if (shell->old_pwd != NULL) // Freeing OLD_PWD     ------ Wijzen env OLD_PWD en shell->old_pwd naar zelfde malloc of verschillende?
		free (shell->old_pwd);
}

// Cleans up all malloced stuff and exits minishell
void	kill_program(t_shell *shell, char *msg, int i)
{
	free_env(shell, &shell->env_list);
	rl_clear_history();
	if (msg != NULL)
	{
		ft_putendl_fd(msg, STDERR_FILENO);
		exit(i);
	}
	exit(EXIT_SUCCESS);
}
