/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/09 10:46:15 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	check_ctable(t_shell *shell) // TESTING PURPOSES
{
	t_ctable	*tmp;
	t_file		*tmp_in;
	t_file		*tmp_out;

	int o = 0;
	int num = 0;
	tmp = shell->input->cnode;
	while (tmp != NULL)
	{
		tmp_in = tmp->infiles;
		tmp_out = tmp->outfiles;
		printf("\n--[NODE: %d]--\n", num);
		while (tmp_in != NULL)
		{
			printf("infile %d: %s ", o, tmp_in->str);
			if (tmp_in->type == t_in_file)
				printf("[< file]\n");
			else if (tmp_in->type == t_in_heredoc)
				printf("[<< heredoc]\n");
			tmp_in = tmp_in->next;
			o++;
		}
		o = 0;
		while (tmp_out != NULL)
		{
			printf("outfile %d: %s ", o, tmp_out->str);
			if (tmp_out->type == t_out_trunc)
				printf("[> trunc]\n");
			else if (tmp_out->type == t_out_append)
				printf("[>> append]\n");
			tmp_out = tmp_out->next;
			o++;
		}
		o = 0;
		while (tmp->cmd_array != NULL && tmp->cmd_array[o] != NULL)
		{
			if (tmp->cmd_array != NULL)
				printf("Cmd %d: %s\n", o, tmp->cmd_array[o]);
			o++;
		}
		o = 0;
		tmp = tmp->next;
		num++;
	}
	printf("\n");
}


// The minishell loop that keeps minishell running. We check if input is correct,
// then add the input to readline history, then split the input into a 2d array
// *** split_input gets replaced by the command table linked list ***
void	ft_minishell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell: ");
		if (input == NULL)
			break ;
		else if (input[0] == '\0')
		{
			free (input);
			continue ;
		}
		add_history(input);
		if (input_checker(&input) == 1)
			continue ;
		create_ctable(shell, input);
		free (input);
		check_ctable(shell); // Testing all files and cmds
		start_execution(shell);
		free_cmd_list(&shell->input->cnode);
	}
	if (input != NULL)
		free (input);
}
