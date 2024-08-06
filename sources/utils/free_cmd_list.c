/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 12:10:51 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/06 16:36:11 by wsonepou      ########   odam.nl         */
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

static void	close_fds(t_ctable *cnode)
{
	if (cnode->hd_pipe[0] != 0 && close(cnode->hd_pipe[0]) == -1)
		printf("Failed closing read-end hd_pipe fd %d\n", cnode->hd_pipe[0]);
	if (cnode->hd_pipe[1] != 0 && close(cnode->hd_pipe[1]) == -1)
		printf("Failed closing write-end hd_pipe fd %d\n", cnode->hd_pipe[0]);
	if (cnode->infile != 0 && close(cnode->infile) == -1)
		printf("Failed closing infile fd %d\n", cnode->hd_pipe[0]);
	if (cnode->outfile != 0 && close(cnode->outfile) == -1)
		printf("Failed closing outfile fd %d\n", cnode->hd_pipe[0]);
	cnode->hd_pipe[0] = 0; // Niet zeker of deze declaraties nodig zijn
	cnode->hd_pipe[1] = 0;
	cnode->infile = 0;
	cnode->outfile = 0;
}

void	free_cmd_list(t_input *input, t_ctable **head)
{
	t_ctable	*tmp;

	if (input->pids != NULL)
		free(input->pids);
	if (*head == NULL)
		return ;
	tmp = *head;
	while (tmp != NULL)
	{
		free_file_list(&tmp->infiles, &tmp->outfiles);
		ft_free_arr(&tmp->cmd_array);
		close_fds(tmp);
		tmp = tmp->next;
		free (*head);
		*head = tmp;
	}
	*head = NULL;
}
