/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 12:10:51 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/27 13:31:23 by mlubbers      ########   odam.nl         */
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
		perror("Failed closing read-end hd_pipe fd");
	if (cnode->hd_pipe[1] != -1 && close(cnode->hd_pipe[1]) == -1)
		perror("Failed closing write-end hd_pipe fd");
	if (cnode->infile != -1 && close(cnode->infile) == -1)
		perror("Failed closing infile fd");
	if (cnode->outfile != -1 && close(cnode->outfile) == -1)
		perror("Failed closing outfile fd");
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
