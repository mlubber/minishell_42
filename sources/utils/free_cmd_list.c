/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 12:10:51 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/15 12:10:57 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_file_list(t_file **infiles, t_file **outfiles)
{
	t_file	*tmp;

	if (*infiles != NULL)
	{
		tmp = (*infiles);
		while (tmp != NULL)
		{
			tmp = tmp->next;
			free ((*infiles)->str);
			free (*infiles);
			(*infiles) = tmp;
		}
	}
	if (*outfiles != NULL)
	{
		tmp = (*outfiles);
		while (tmp != NULL)
		{
			tmp = tmp->next;
			free ((*outfiles)->str);
			free (*outfiles);
			(*outfiles) = tmp;
		}
	}
}

void	free_cmd_list(t_ctable **head)
{
	t_ctable	*tmp;
	int			i;

	i = 0;
	if (*head == NULL)
		return ;
	tmp = *head;
	while (tmp != NULL)
	{
		free_file_list(&tmp->infiles, &tmp->infiles);
		if (tmp->cmd_array != NULL)
		{
			i = 0;
			while (tmp->cmd_array[i] != NULL)
			{
				free(tmp->cmd_array[i]);
				i++;
			}
			free (tmp->cmd_array);
		}
		tmp = tmp->next;
		free (*head);
		*head = tmp;
	}
	*head = NULL;
}
