/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/19 16:36:08 by mlubbers      ########   odam.nl         */
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
		printf("\n--[NODE: %d]--\n", num + 1);
		while (tmp_in != NULL)
		{
			printf("infile %d: %s ", o + 1, tmp_in->str);
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
			printf("outfile %d: %s ", o + 1, tmp_out->str);
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
				printf("Cmd %d: [%s]\n", o + 1, tmp->cmd_array[o]);
			o++;
		}
		o = 0;
		tmp = tmp->next;
		num++;
	}
	printf("\n");
}

static void	reset_input_values(t_shell *shell, t_input *input)
{
	input->var_len = 0;
	input->var_val_len = 0;
	input->word_len = 0;
	input->cmd_seg = 0;
	input->node_count = 0;
	shell->input->pids = NULL;
	if (dup2(shell->stdinput, STDIN_FILENO) == -1)
		kill_program(shell, "Failed resetting stdin", errno);
	if (dup2(shell->stdoutput, STDOUT_FILENO) == -1)
		kill_program(shell, "Failed resetting stdout", errno);
}


// The minishell loop that keeps minishell running. We check if input is correct,
// then add the input to readline history, then split the input into a 2d array
void	ft_minishell_loop(t_shell *shell, int argc, char **argv)
{
	if (argc > 1 && ft_strncmp(argv[1], "-c", 2) == 0 && argv[2] != NULL)
	{
		create_ctable(shell, argv[2]);
		start_execution(shell);
		free_cmd_list(shell->input, &shell->input->cnode);
	}
	else
	{
		while (1)
		{
			// printf("ec %d\n", shell->exit_code);
			reset_input_values(shell, shell->input);
			shell->input->line = readline("minishell: ");
			if (shell->input->line == NULL)
				break ;
			else if (shell->input->line[0] == '\0' )
			{
				free (shell->input->line);
				continue ;
			}
			add_history(shell->input->line);
			if (input_checker(shell, shell->input->line) > 0)
			{
				// printf("we continue\n");
				continue ;
			}
			create_ctable(shell, shell->input->line);
			free (shell->input->line);
			// check_ctable(shell); // Testing all files and cmds
			start_execution(shell);
			free_cmd_list(shell->input, &shell->input->cnode);
		}
		printf("out of while loop\n");
	}
}
