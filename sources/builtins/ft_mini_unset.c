/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 12:10:52 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/07 13:04:44 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	delete_var(t_list **head, int position)
// {
// 	t_list	*tmp;
// 	t_list	*old;

// 	tmp = *head;
// 	old = NULL;
// 	if (*head == NULL)
// 		printf("DEL MID: Linked List already empty!\n");
// 	else if (position == 1)
// 	{
// 		*head = (*head)->next;
// 		free(tmp);
// 	}
// 	else if (position > count_nodes(*head))
// 	{
// 		printf("Node #%d is bigger than list size\n", position);
// 		exit(1);
// 	}
// 	else if (position == count_nodes(*head))
// 	{
// 		while (tmp->next->next != NULL)
// 			tmp = tmp->next;
// 		free(tmp->next);
// 		tmp->next = NULL;
// 	}
// 	else
// 	{
// 		while (position > 2)
// 		{
// 			tmp = tmp->next;
// 			position--;
// 		}
// 		old = tmp->next;
// 		tmp->next = tmp->next->next;
// 		free(old);
// 	}
// }

int	ft_mini_unset(t_shell *shell, char **split_input)
{
	int		i;
	int		pos;
	t_env	*tmp;

	i = 0;
	pos = 0;
	tmp = shell->env_list;
	if (split_input[1] == NULL)
		return (1);
	while (split_input[i] != NULL)
	{
		while (tmp != NULL)
		{
			if (ft_strncmp(tmp->var_name, split_input[i], ft_strlen(split_input[i]) + 1) == 0)
			{
				// delete_var(tmp, i);
				break ;
			}
			pos++;
		}
		pos = 0;
		i++;		
	}
	return (1);
}
