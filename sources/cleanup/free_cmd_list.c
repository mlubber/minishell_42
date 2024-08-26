/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 12:10:51 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/21 19:37:07 by wsonepou      ########   odam.nl         */
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
	if (cnode->hd_pipe[0] != -1 && close(cnode->hd_pipe[0]) == -1)
		printf("Failed closing read-end hd_pipe fd %d\n", cnode->hd_pipe[0]);
	if (cnode->hd_pipe[1] != -1 && close(cnode->hd_pipe[1]) == -1)
		printf("Failed closing write-end hd_pipe fd %d\n", cnode->hd_pipe[0]);
	if (cnode->infile != -1 && close(cnode->infile) == -1)
		printf("Failed closing infile fd %d\n", cnode->hd_pipe[0]);
	if (cnode->outfile != -1 && close(cnode->outfile) == -1)
		printf("Failed closing outfile fd %d\n", cnode->hd_pipe[0]);
	cnode->hd_pipe[0] = -1;
	cnode->hd_pipe[1] = -1;
	cnode->infile = -1;
	cnode->outfile = -1;
}

void	free_cmd_list(t_ctable **head)
{
	t_ctable	*tmp;

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
