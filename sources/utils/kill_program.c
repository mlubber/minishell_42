/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kill_program.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 14:08:00 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/07 15:04:06 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_free_2d_arr(char ***arr, int i)
{
	if (arr == NULL || *arr == NULL)
		return NULL;
	if (i > 0)
	{
		while (i >= 0)
		{
			if ((*arr)[i] != NULL)
				free((*arr)[i]);
			i++;
		}
		free (*arr);
		return (NULL);
	}
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	return (NULL);
}

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

void	free_env(t_shell *shell, t_env **env_head)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (shell->paths != NULL) // Freeing paths
	{
		while (shell->paths[i] != NULL)
		{
			free(shell->paths[i]);
			i++;
		}
		free(shell->paths);
	}
	tmp = *env_head;
	while (env_head != NULL && tmp != NULL) // Freeing ENV linked list
	{
		tmp = tmp->next;
		if (*env_head != NULL)
			free_env_node(env_head);
		*env_head = tmp;
	}
	if (shell->pwd != NULL) // Freeing PWD
		free (shell->pwd);
	if (shell->old_pwd != NULL) // Freeing OLD_PWD
		free (shell->old_pwd);
}


void	kill_program(t_shell *shell, char *msg, int i)
{
	free_env(shell, &shell->env_list);
	rl_clear_history();
	if (shell->input != NULL)
		free (shell->input);
	if (msg != NULL)
	{
		printf("%s\n", msg);
		exit(i);
	}
	exit(EXIT_SUCCESS);
}
