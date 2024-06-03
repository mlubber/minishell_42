/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kill_program.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 14:08:00 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/03 19:41:19 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_free_2d_arr(char **arr) // No longer needed?
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// }


void	free_env_node(t_env **node)
{
	free((*node)->var_name);
	free((*node)->var_val);
	free(*node);
}


void	delete_list(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	if(*head == NULL)
		return ;
	else
	{
		while (tmp != NULL)
		{
			tmp = tmp->next;
			free_env_node(head);
			*head = tmp;
		}
	}
}


void	kill_program(t_tools *tools, char *msg, int i)
{
	if (tools->envp != NULL)
		delete_list(&tools->env_list);
	if (msg != NULL)
	{
		printf("%s\n", msg);
		exit(i);
	}
	exit(EXIT_SUCCESS);
}
