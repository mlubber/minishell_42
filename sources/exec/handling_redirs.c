/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handling_redirs.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 14:35:10 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/23 16:17:23 by mlubbers      ########   odam.nl         */
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
		input = get_next_line(0);
		if (input == NULL)
			break ;
		if (strncmp(input, infile->str, limiter_len) == 0
			&& input[limiter_len] == '\n')
		{
			free(input);
			break ;
		}
		write(cnode->hd_pipe[1], input, ft_strlen(input));
		free (input);
	}
	if (dup2(cnode->hd_pipe[0], STDIN_FILENO) == -1)
		kill_program(shell, "child dup2 fds[0]", errno);
	// if (close(cnode->hd_pipe[1]) == -1)
	// 	printf("Failed closing hd_pipe write end");
}

static char	*open_outfiles(t_shell *shell, t_ctable *cnode, t_file *outfile)
{
	t_file	*tmp;

	tmp = cnode->outfiles;
	while (outfile != NULL)
	{
		if (cnode->outfile != 0)
			if (close(cnode->outfile) == -1)
				printf("Failed closing outfile fd %d\n", cnode->outfile);
		if (outfile->type == t_out_trunc)
			cnode->outfile = open(outfile->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else
			cnode->outfile = open(outfile->str, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (cnode->outfile == -1)
			return (outfile->str);
		if (dup2(cnode->outfile, STDOUT_FILENO) == -1)
			kill_program(shell, "Failed dup2 infile", errno);
		outfile = outfile->next;
	}
	return (NULL);
}

// Few different cases to check for:
// -- No infiles & heredocs
// -- Infiles but no heredocs
// -- No infiles, but heredocs
// -- Both infiles and heredocs, but last is an infile
// -- Both infiles and heredocs, but last is a heredoc
static char	*open_infiles(t_shell *shell, t_ctable *cnode, t_file *infile)
{
	while (infile != NULL)
	{
		if (infile->type == t_in_file)
		{
			if (cnode->infile != 0)
				if (close(cnode->infile) == -1)
					printf("Failed closing infile fd %d\n", cnode->infile);
			cnode->infile = open(infile->str, O_RDONLY);
			if (cnode->infile == -1)
				return (infile->str);
			if (dup2(cnode->infile, STDIN_FILENO) == -1)
				kill_program(shell, "Failed dup2 infile", errno);
		}
		else if (infile->type == t_in_heredoc && infile->next == NULL)
		{
			if (cnode->infile != 0)
				if (close(cnode->infile) == -1)
					printf("Failed closing infile fd %d\n", cnode->infile);
			ft_heredoc(shell, cnode, cnode->infiles);
		}
		infile = infile->next;
	}
	return (NULL);
}


bool	handling_redirs(t_shell *shell, t_ctable *cnode)
{
	t_file	*infile;
	char	*file;

	infile = cnode->infiles;
	while (infile != NULL)
	{
		// if (infile->type == t_in_heredoc)
		// 	ft_heredoc(infile);
		infile = infile->next;
	}
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
