/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handling_redirs.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 14:35:10 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/09/02 11:41:20 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ambiguous_redirect(char *file)
{
	errno = 1;
	return (file);
}

static void	set_heredoc_in(t_shell *shell, t_ctable *cnode)
{
	if (dup2(cnode->hd_pipe[0], STDIN_FILENO) == -1)
		kill_program(shell, "dup2 infile", errno);
	if (close(cnode->hd_pipe[0]) == -1)
		perror("Failed closing heredoc pipe[0]");
	cnode->hd_pipe[0] = -1;
}

static char	*open_infiles(t_shell *shell, t_ctable *cnode, t_file *infile)
{
	while (infile != NULL)
	{
		if (infile->type == t_in_file)
		{
			if (infile->str[0] == '$' && (infile->str[1] == '_'
					|| ft_isalnum(infile->str[1])))
				return (ambiguous_redirect(infile->str));
			if (access(infile->str, F_OK | R_OK) == -1)
				if (errno == 13)
					return (infile->str);
			cnode->infile = open(infile->str, O_RDONLY);
			if (cnode->infile == -1)
				return (infile->str);
			if (dup2(cnode->infile, STDIN_FILENO) == -1)
				kill_program(shell, "dup2 infile", errno);
			if (close(cnode->infile) == -1)
				perror("Failed closing infile");
			cnode->infile = -1;
		}
		else if (infile->type == t_in_heredoc && infile->next == NULL)
			set_heredoc_in(shell, cnode);
		infile = infile->next;
	}
	return (NULL);
}

static char	*open_outfiles(t_shell *shell, t_ctable *cnode, t_file *outfile)
{
	while (outfile != NULL)
	{
		if (outfile->str[0] == '$' && (outfile->str[1] == '_'
				|| ft_isalnum(outfile->str[1])))
			return (ambiguous_redirect(outfile->str));
		if (outfile->type == t_out_trunc)
			cnode->outfile
				= open(outfile->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else
			cnode->outfile
				= open(outfile->str, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (cnode->outfile == -1)
			return (outfile->str);
		if (dup2(cnode->outfile, STDOUT_FILENO) == -1)
			kill_program(shell, "dup2 outfile", errno);
		if (close(cnode->outfile) == -1)
			perror("Failed closing outfile");
		cnode->outfile = -1;
		outfile = outfile->next;
	}
	return (NULL);
}

char	*handling_redirs(t_shell *shell, t_ctable *cnode, int node_nr, int x)
{
	char	*file;

	if (node_nr != shell->input->node_count - 1 && x != 0)
		if (dup2(shell->input->fds[1], STDOUT_FILENO) == -1)
			kill_program(shell, "Child stdout dup fail", errno);
	closing_fds(shell);
	file = open_infiles(shell, cnode, cnode->infiles);
	if (file != NULL)
		return (file);
	file = open_outfiles(shell, cnode, cnode->outfiles);
	if (file != NULL)
		return (file);
	return (NULL);
}
