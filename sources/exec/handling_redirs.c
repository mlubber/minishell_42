/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handling_redirs.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 14:35:10 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/12 14:59:03 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_heredoc(t_shell *shell, t_ctable *cnode, t_file *infile)
{
	char	*input;
	int		limiter_len;

	limiter_len = ft_strlen(infile->str);
	if (pipe(cnode->hd_pipe) == -1)
		kill_program(shell, "Failed creating pipe", errno);
	while (1)
	{
		input = get_next_line(shell->stdinput);
		if (input == NULL)
			break ;
		if (ft_strncmp(input, infile->str, limiter_len) == 0
			&& input[limiter_len] == '\n')
		{
			free(input);
			break ;
		}
		write(cnode->hd_pipe[1], input, ft_strlen(input));
		free (input);
	}
	if (dup2(cnode->hd_pipe[0], STDIN_FILENO) == -1)
		kill_program(shell, "heredoc dup2 hd_pipe[0], STDIN failed", errno);
	if ((close(cnode->hd_pipe[1]) == -1) || (close(cnode->hd_pipe[0]) == -1))
		printf("Failed closing hd_pipe write end");
}

static char	*open_infiles(t_shell *shell, t_ctable *cnode, t_file *infile)
{
	while (infile != NULL)
	{
		if (infile->type == t_in_file)
		{
			cnode->infile = open(infile->str, O_RDONLY);
			if (cnode->infile == -1)
				return (infile->str);
			if (dup2(cnode->infile, STDIN_FILENO) == -1)
				kill_program(shell, "Failed dup2 infile", errno);
			if (close(cnode->infile) == -1)
				printf("Failed closing infile %s\n", infile->str);
			cnode->infile = 0;
		}
		else if (infile->type == t_in_heredoc && infile->next == NULL)
			ft_heredoc(shell, cnode, infile);
		infile = infile->next;
	}
	return (NULL);
}

static char	*open_outfiles(t_shell *shell, t_ctable *cnode, t_file *outfile)
{
	while (outfile != NULL)
	{
		if (outfile->type == t_out_trunc)
			cnode->outfile = open(outfile->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else
			cnode->outfile = open(outfile->str, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (cnode->outfile == -1)
			return (outfile->str);
		if (dup2(cnode->outfile, STDOUT_FILENO) == -1)
			kill_program(shell, "Failed dup2 infile", errno);
		if (close(cnode->outfile) == -1)
			printf("Failed closing hd_pipe write end");
		cnode->outfile = 0;
		outfile = outfile->next;
	}
	return (NULL);
}

bool	handling_redirs(t_shell *shell, t_ctable *cnode, int node_nr)
{
	char	*file;

	if (node_nr != shell->input->node_count - 1)
		if (dup2(shell->input->fds[1], STDOUT_FILENO) == -1)
			kill_program(shell, "Child stdout dup fail", errno);
	closing_fds(shell);
	file = open_infiles(shell, cnode, cnode->infiles);
	if (file != NULL)
	{
		printf("Error: Couldn't open file: %s\n", file);
		return (false);
	}
	file = open_outfiles(shell, cnode, cnode->outfiles);
	if (file != NULL)
	{
		printf("Error: Couldn't open file: %s\n", file);
		return (false);
	}
	return (true);
}
