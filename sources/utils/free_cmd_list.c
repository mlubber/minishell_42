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
		if (tmp->cmds != NULL)
		{
			while (tmp->cmds[i] != NULL)
			{
				free(tmp->cmds[i]);
				i++;
			}
			free (tmp->cmds);
		}
		tmp = tmp->next;
		free (*head);
		*head = tmp;
	}
	*head = NULL;
}
